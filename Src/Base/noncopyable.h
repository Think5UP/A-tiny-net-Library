//
// Created by root on 2/13/23.
//

#ifndef NET_LIB_NONCOPYABLE_H
#define NET_LIB_NONCOPYABLE_H

namespace net_lib {
    class noncopyable {
    public:
        noncopyable(const noncopyable &) = delete;
        noncopyable &operator=(const noncopyable&) = delete;

    protected:
        noncopyable() = default;
        ~noncopyable() = default;
    };
}
#endif //NET_LIB_NONCOPYABLE_H
