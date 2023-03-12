//
// Created by root on 23-2-13.
//

#ifndef NET_LIB_TYPES_H
#define NET_LIB_TYPES_H

#include <string>
#include <string.h>
#include <stdint.h>

#ifndef NDEUG
#include <assert.h>
#endif

namespace net_lib{

    using std::string;

    inline void memZero(void* p, size_t n){
        memset(p, 0, n);
    }

    template<typename To,typename From>
    inline To implecit_cast(From const &f){
        return f;
    }

    template<typename To,typename From>
    inline To down_cast(From *f){
        if(false){
            implecit_cast<From*,To>(0);
        }
        #if !defined(NDEBUG) && !defined(GOOGLE_PROTOBUF_NO_RTTi)
            assert(f == NULL || dynamic_cast<To>(f) != NULL);
        #endif
        return static_cast<To>(f);
    }
}//end of net_lib
#endif //NET_LIB_TYPES_H
