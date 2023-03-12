//
// Created by root on 23-2-14.
//

#include <cstdio>
#include <sys/time.h>

//为了使用PRId64所以需要使用__STDC_FORMAT_MACROS这个宏以及inttype.h这个头文件
#ifndef __STDC_FORMAT_MACROS
#define  __STDC_FORMAT_MACROS
#endif
#include <cinttypes>


#include "Timestamp.h"

namespace net_lib{

    static_assert(sizeof (Timestamp) == sizeof(int64_t),
                  "Timestamp should be same size as int64_t");

//获取当前的时间初始化时间戳
    Timestamp Timestamp::now() {
        struct timeval tv;
        gettimeofday(&tv,NULL);
        int64_t seconds = tv.tv_sec;
        return Timestamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);
    }

//将秒与毫秒存入buf中，并返回
    std::string Timestamp::toString() const {
        char buf[32] = "0";
        int64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
        int64_t microSeconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;
        /*因为在32位和64位系统中int64_t不同，为了跨平台所以使用PRId64来打印int64_t类型的值
          在64位系统中int64_t代表的是long int
          32位中是long long int*/
        snprintf(buf, sizeof(buf), "%" PRId64 ".%06" PRId64 "", seconds, microSeconds);
        return buf;
    }

    std::string Timestamp::toFormattedString(bool showMicroSeconds) const {
        char buf[64];
        struct tm tm_time;
        time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
        gmtime_r(&seconds,&tm_time);

        if(showMicroSeconds){
            int microSeconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
            //格式 年月日 时:分:秒:微秒
            snprintf(buf,sizeof(buf),"%4d-%02d-%02d %02d:%02d:%02d.%06d",
                     tm_time.tm_year + 1900,tm_time.tm_mon + 1,tm_time.tm_mday,
                     tm_time.tm_hour,tm_time.tm_min,tm_time.tm_sec
                    ,microSeconds);
        }else{
            snprintf(buf,sizeof(buf),"%4d-%02d-%02d %02d:%02d:%02d",
                     tm_time.tm_year + 1900,tm_time.tm_mon + 1,tm_time.tm_mday,
                     tm_time.tm_hour,tm_time.tm_min,tm_time.tm_sec);
        }
        return buf;
    }

}