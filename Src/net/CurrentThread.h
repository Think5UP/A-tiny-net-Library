//
// Created by root on 2/22/23.
//

#ifndef NET_LIB_CURRENTTHREAD_H
#define NET_LIB_CURRENTTHREAD_H

#include <unistd.h>
#include <sys/syscall.h>

namespace CurrentThread{
    extern __thread int t_cacheTid;
    void cacheTid();

    inline int tid(){
        if(__builtin_expect(t_cacheTid == 0,0)){
            cacheTid();
        }
        return t_cacheTid;
    }

}

#endif //NET_LIB_CURRENTTHREAD_H
