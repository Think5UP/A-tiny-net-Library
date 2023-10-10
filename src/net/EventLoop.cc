#include "EventLoop.h"

#include <fcntl.h>
#include <sys/eventfd.h>
#include <unistd.h>

#include "Channel.h"
#include "Logging.h"
#include "poller.h"

// 本地线程变量
// 防止当前线程创建多个loop
// 初始化完成会将这个变量指向对应的loop
__thread EventLoop *t_loopInThisThread = nullptr;

// 默认的poller IO端口复用的超时时间
const int kPollTimeMS = 1000;

int createEventfd() {
  int eventfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
  if (eventfd < 0) {
    LOG_FATAL << __FILE__ << ":" << __LINE__ << " eventfd failed: " << errno;
  }
  return eventfd;
}

EventLoop::EventLoop()
    : looping_(false),
      quit_(false),
      callingPendingFunctors_(false),
      threadId_(CurrentThread::tid()),
      poller_(Poller::newDefaultPoller(this)),
      timerQueue_(new TimerQueue(this)),
      wakeupFd_(createEventfd()),
      wakeupChannel_(new Channel(this, wakeupFd_)),
      currentActiveChannel_(nullptr) {
  LOG_DEBUG << "EventLoop create " << this << "the threadId_ is " << threadId_;
  LOG_DEBUG << "EventLoop create " << this << "the wakeupFd_ is "
            << wakeupChannel_->fd();
  if (t_loopInThisThread) {
    LOG_FATAL << "Another EventLoop" << t_loopInThisThread
              << " exists in this thread " << threadId_;
  } else {
    t_loopInThisThread = this;
  }
  // 设置wakeupfd的事件类型以及发生事件的回调函数
  wakeupChannel_->setReadCallBack(std::bind(&EventLoop::handleRead, this));
  // 每一个EventLoop都将监听wakeupChannel的EPOLLIN事件
  wakeupChannel_->enableReadEvent();
}

EventLoop::~EventLoop() {
  // channel移除所有感兴趣事件
  wakeupChannel_->disAllEvent();
  // 将channel从EventLoop中删除
  wakeupChannel_->remove();
  ::close(wakeupChannel_->fd());
  t_loopInThisThread = nullptr;
}

void EventLoop::loop() {
  looping_ = true;
  quit_ = false;

  LOG_INFO << "EventLoop" << this << " is start";

  while (!quit_) {
    activeChannels_.clear();
    // 通过epoll获取监听到事件的channel 然后分别处理回调
    pollReturnTime_ = poller_->poll(kPollTimeMS, &activeChannels_);
    for (auto *channel : activeChannels_) {
      channel->handleEvent(pollReturnTime_);
    }
    /**
     * IO thread：mainLoop accept fd 打包成 chennel 分发给 subLoop
     * mainLoop实现注册一个回调，交给subLoop来执行，wakeup subLoop
     * 之后，让其执行注册的回调操作 这些回调函数在 std::vector<Functor>
     * pendingFunctors_; 之中
     */
    doPendingFunctors();
  }
  looping_ = false;
}

void EventLoop::quit() {
  quit_ = true;
  if (isInLoopThread()) {
    wakeup();
  }
}

// 在属于自己的线程中处理回调
void EventLoop::runInLoop(Functor cb) {
  if (isInLoopThread()) {
    cb();
  } else {
    queueInLoop(cb);
  }
}

// 当前处理回调不在自己属于的线程中
void EventLoop::queueInLoop(Functor cb) {
  {
    // 不在自己的线程中就先将回调添加入pendingFunctors_中
    // 等待接下来唤醒线程后处理
    std::unique_lock<std::mutex> lock(mutex_);
    pendingFunctors_.emplace_back(cb);
  }
  // 这里需要确保无论是不在属于自己的线程
  // 或者是正在处理挂起任务中都能正确的唤醒线程 防止阻塞
  if (!isInLoopThread() || callingPendingFunctors_) {
    wakeup();
  }
}

void EventLoop::wakeup() {
  // 通过向wakeupFd_发八个字节来唤醒线程
  uint64_t one = 1;
  ssize_t n = write(wakeupFd_, &one, sizeof(one));
  if (n != sizeof(one)) {
    LOG_ERROR << "EventLoop::wakeup writes " << n << " bytes instead of 8";
  }
}

void EventLoop::updateChannel(Channel *channel) {
  // 因为channel和poller是不互通的
  // 所以channel会先通过Channel=>update()将需要更新的内容发给管理自己的loop
  // 再接着真正修改到poller中
  poller_->updataChannel(channel);
}

void EventLoop::removeChannel(Channel *channel) {
  // remove同update
  poller_->removeChannel(channel);
}

bool EventLoop::hasChannel(Channel *channel) {
  return poller_->hasChannel(channel);
}

void EventLoop::handleRead() {
  uint64_t one = 1;
  ssize_t n = read(wakeupFd_, &one, sizeof(one));
  if (n != sizeof(one)) {
    LOG_ERROR << "EventLoop::handleRead read " << n << " bytes instead of 8";
  }
}

void EventLoop::doPendingFunctors() {
  std::vector<Functor> functors;
  callingPendingFunctors_ = true;

  // 这里直接将挂起的任务转移就不用慢慢遍历callingPendingFunctors_
  // 其他线程就能直接将挂起的任务继续往callingPendingFunctors_里写
  // 不用等到挂起任务全部处理完
  {
    std::unique_lock<std::mutex> lock(mutex_);
    functors.swap(pendingFunctors_);
  }
  for (const auto &functor : functors) {
    functor();
  }
  callingPendingFunctors_ = false;
}
