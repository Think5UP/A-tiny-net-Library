//
// Created by root on 3/20/23.
//

#ifndef NET_LIB_HTTPREQUEST_H
#define NET_LIB_HTTPREQUEST_H

#include <map>
#include <string>

#include "../Base/copyable.h"
#include "../Base/Timestamp.h"

class HttpRequest : public net_lib::copyable{
public:
    enum Method {
        kInvalid,   //构造中设置的默认模式
        kGet,       //请求指定的页面信息，并返回实体主体。
        kPost,      //向指定资源提交数据进行处理请求(例如提交表单或者上传文件).数据被包含在请求体中.POST 请求可能会导致新的资源的建立和/或已有资源的修改。
        kHead,      //类似于 GET 请求，只不过返回的响应中没有具体的内容，用于获取报头
        kPut,       //从客户端向服务器传送的数据取代指定的文档的内容。
        kDelete     //请求服务器删除指定的页面.
    };

    enum Version{
        kUnknown,
        kHttp10,
        kHttp11
    };

    HttpRequest() : method_(kInvalid),
                    version_(kUnknown){

    }
    ~HttpRequest(){}

    bool setMethod(const char *method) {
#define XX(Me, m)                       \
    if(method == #m){                   \
        method_ = Method::Me;           \
    }
        XX(kGet, get);
        XX(kPost, post);
        XX(kHead, head);
        XX(kPut, put);
        XX(kDelete, Delete);
#undef XX
        return method_ != kInvalid;
    }

    Method method() const { return method_; }

     const char* MethodToString() const {
        switch (method_) {
#define XX(name)                    \
        case Method::name:           \
            return #name;           \
            break;
            XX(kGet);
            XX(kPost);
            XX(kHead);
            XX(kPut);
            XX(kDelete);
#undef XX
            default:
                return "kInvalid";
        }
        return "ERROR";
    }

    void setVersion(Version v){ version_ = v; }
    Version version() const { return version_; }

    void setPath(const char* start,const char* end) { path_.assign(start,end); }
    const std::string &getPath() const { return path_; }

    void setQuery(const char* start,const char* end) { query_.assign(start, end); }
    const std::string &getQuery() const { return query_; }

    void setReceiveTime(net_lib::Timestamp t) { receiveTime_ = t; }
    net_lib::Timestamp getReceiveTime() const { return receiveTime_; }

    //将请求截取,将头部和内容拆分存入map
    void addHeader(const char* start,const char* colon,const char* end){
        std::string field(start,colon);
        //冒号之前不允许有空格
        ++colon;
        while (colon < end && isspace(*colon)){
            ++colon;
        }
        //将value后面的空格丢弃,通过resize截断
        std::string value(colon,end);
        while(!value.empty() && isspace(value[value.size() - 1])){
            value.resize(value.size() - 1);
        }
        header_[field] = value;
    }

    //获取请求头部的值
    const std::string &getHeader(const std::string &field) const {
        std::string result;
        std::map<std::string,std::string>::const_iterator it = header_.find(field);
        if(it != header_.end()){
            result = it->second;
        }
        return result;
    }

    std::map<std::string,std::string> Header() const { return header_; }

    void swap(HttpRequest& rhs){
        std::swap(method_,rhs.method_);
        std::swap(version_,rhs.version_);
        path_.swap(rhs.path_);
        query_.swap(rhs.query_);
        std::swap(receiveTime_,rhs.receiveTime_);
        header_.swap(rhs.header_);
    }
private:
    Method method_;
    Version version_;
    std::string path_;
    std::string query_;
    net_lib::Timestamp receiveTime_;
    std::map<std::string,std::string> header_;
};

#endif //NET_LIB_HTTPREQUEST_H
