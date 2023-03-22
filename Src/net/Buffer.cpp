//
// Created by root on 3/6/23.
//

#include <cerrno>
#include <sys/uio.h>

#include "Buffer.h"

namespace net_lib{

    const char Buffer::kCRLF[] = "\r\n";

    ssize_t Buffer::readfd(int fd, int *saveErrno) {
        //初始化一段栈上的内存空间作为临时的缓冲区
        char extraBuf[65536] {0};
        const size_t writable = writableBytes();
        struct iovec vec[2];
        vec[0].iov_base = begin() + writerIndex_;
        vec[0].iov_len = writable;

        vec[1].iov_base = extraBuf;
        vec[1].iov_len = sizeof(extraBuf);

        int iovcnt = (writable < sizeof(extraBuf) ? 2 : 1);
        ssize_t n = ::readv(fd,vec,iovcnt);
        if(n < 0){
            *saveErrno = errno;
        } else if(n <= (ssize_t)writable){
            writerIndex_ += n;
        } else {
            //缓冲区中reader空间不够了,将writer的下标移动到buffer_的尾部
            writerIndex_ = buffer_.size();
            //将后续的内容读取到暂时的缓冲区中
            append(extraBuf, sizeof(n - writable));
        }
        return n;
    }
}

