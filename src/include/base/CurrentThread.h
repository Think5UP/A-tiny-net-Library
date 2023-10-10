#ifndef CURRENT_THREAD_H_
#define CURRENT_THREAD_H_

#include <sys/syscall.h>
#include <unistd.h>

namespace CurrentThread {
extern __thread int t_cachedTid;  // 保存tid的缓冲 避免多次的系统调用

void cacheTid();

inline int tid() {
  // 分支预测 这里代表t_cachedTid == 0为假的可能性更大
  // 因为这里是获取线程id 除非出错 不然正常的tid都缓存在t_cachedTid中
  // 所以这里分支预测会将t_cachedTid == 0认为是假的可能性高
  if (__builtin_expect(t_cachedTid == 0, 0)) {
    cacheTid();
  }
  return t_cachedTid;
}

}  // namespace CurrentThread

#endif  // !CURRENT_THREAD_H_
