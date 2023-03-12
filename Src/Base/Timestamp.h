//
// Created by root on 23-2-13.
//

#ifndef NET_LIB_TIMESTAMP_H
#define NET_LIB_TIMESTAMP_H

#include "copyable.h"
#include "Types.h"

namespace net_lib {
    class Timestamp{
    public:
        //构造无效的时间戳
        Timestamp() : microSecondsSinceEpoch_(0) {}
        //构造特殊时间的时间戳
        explicit Timestamp(int64_t microSecondsSinceEpochArg) : microSecondsSinceEpoch_(microSecondsSinceEpochArg) {}
        //交换时间戳
        void swap(Timestamp &ts) {
            std::swap(microSecondsSinceEpoch_,ts.microSecondsSinceEpoch_);
        }
        //序列化
        std::string toString() const;
        std::string toFormattedString(bool showMicroSeconds = false ) const;

        bool valid()const{return microSecondsSinceEpoch_ > 0;}

        int64_t microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }
        time_t SecondsSinceEpoch() const {
            return static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
        }

        static Timestamp now();
        static Timestamp invalid(){
            return Timestamp();
        }

        static Timestamp fromUnixTime(time_t t){
            return fromUnixTime(t,0);
        }
        static Timestamp fromUnixTime(time_t t,int64_t microSeconds){
            return Timestamp(static_cast<int64_t>(t)*kMicroSecondsPerSecond+microSeconds);
        }

        static const int kMicroSecondsPerSecond = 1000 * 1000;
    private:
        int64_t microSecondsSinceEpoch_;
    };

//重载< 与 == 运算符
    inline bool operator<(Timestamp& lhs,Timestamp& rhs){
        return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
    }
    inline bool operator==(Timestamp& lhs,Timestamp& rhs){
        return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
    }

//获取两个时间戳的差，以秒为单位返回
    inline double timeDifference(Timestamp high,Timestamp low){
        int64_t delta = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
        return static_cast<double>(delta) / Timestamp::kMicroSecondsPerSecond;
    }

//给Timestamp增加时间
    inline Timestamp addTime(Timestamp& timestamp,double seconds){
        double delta =  static_cast<int64_t>(seconds * Timestamp::kMicroSecondsPerSecond);
        return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
    }

}
#endif //NET_LIB_TIMESTAMP_H
