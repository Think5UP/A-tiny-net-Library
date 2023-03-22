//
// Created by root on 3/21/23.
//
#include "HttpContext.h"
#include "../net/Buffer.h"

bool HttpContext::parseRequest(net_lib::Buffer *buf, net_lib::Timestamp receiveTime) {
    bool ok = true;
    bool hasMore = true;
    while(hasMore){
        //解析请求行
        if(state_ == kExpectRequestLine){
            //查找buf中第一次出现\r\n的位置
            const char *crlf = buf->findCRLF();
            //找到了
            if(crlf){
                //解析请求行中的内容，打成HttpRequest
                ok = processRequestLine(buf->peek(),crlf);//对readerIndex_到第一个找到CRLF位置的地方处理请求行
                if(ok){
                    request_.setReceiveTime(receiveTime);
                    //将buf的readrIndex_移动到crlf+2的位置开始解析请求头
                    buf->retrieveUntil(crlf + 2);
                    //改变状态开始解析请求头
                    state_ = kExpectHeader;
                } else {
                    hasMore = false;
                }
            } else {
                hasMore = false;
            }
        } else if(state_ == kExpectHeader){ //开始解析请求头
            //找到了请求头的CRLF
            const char *crlf = buf->findCRLF();
            if(crlf){
                const char *colon = std::find(buf->peek(),crlf,':');
                //找到了分隔符
                if(colon != crlf){
                    request_.addHeader(buf->peek(),colon,crlf);
                } else {
                    state_ = kExpectBody;
                }
                buf->retrieveUntil(crlf + 2);
            } else {
                hasMore = false;
            }
        } else if(state_ == kExpectBody){
            //如果buf中还有数据那剩下的一定是请求体
            if(buf->readableBytes()){
                request_.setQuery(buf->peek(),buf->beginWrite());
            }
            state_ = kGotAll;
            hasMore = false;
        }
    }
    return ok;
}

bool HttpContext::processRequestLine(const char *begin, const char *end) {
    bool success = false;
    const char *start = begin;
    //找到第一个空格出现的地方
    const char *space = std::find(start,end,' ');
    //不是最后一个空格并且请求方法设置成功
    if(space != end && request_.setMethod(start,space)){
        //跳过第一个空格,继续寻找下一个空格
        start = space + 1;
        space = std::find(start,end,' ');
        if(space != end){
            //查看是否有请求
            const char *question = std::find(start,space,'?');
            if(question != space){
                //将start到？之前的内容设置为请求路径
                request_.setPath(start,question);
                //？之后到第二个空格前的内容转化为请求队列
                request_.setQuery(question,space);
            } else {
                //无请求参数那就说明只有请求路径
                request_.setPath(start,space);
            }
            //继续跨过这个空格
            start = space + 1;
            success = end-start == 8 && std::equal(start, end-1, "HTTP/1.");
            if(success){
                if(*(end - 1) == '1'){
                    request_.setVersion(HttpRequest::Version::kHttp11);
                } else if(*(end - 1) == '0'){
                    request_.setVersion(HttpRequest::Version::kHttp10);
                }
            }
        }
    }
    return success;
}