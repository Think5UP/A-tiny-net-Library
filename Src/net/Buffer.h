//
// Created by root on 3/6/23.
//

#ifndef NET_LIB_BUFFER_H
#define NET_LIB_BUFFER_H

#include <vector>
#include <string>
#include <algorithm>

namespace net_lib{
    class Buffer{
    public:
        static const size_t kCheapPrepend = 8;//头部八个字节
        static const size_t kInitialSize = 1024;//缓冲区默认大小1k

        explicit Buffer(size_t InitialSize = kInitialSize)
                : buffer_(kCheapPrepend + InitialSize),
                  readerIndex_(kCheapPrepend),
                  writerIndex_(kCheapPrepend){
        }
        //返回可读数据的大小
        size_t readableBytes() const {
            return writerIndex_ - readerIndex_;
        }
        //返回可写数据的大小
        size_t writableBytes() const {
            return buffer_.size() - writerIndex_;
        }
        //返回头部字节大小
        size_t prependableBytes() const {
            return readerIndex_;
        }
        //返回缓冲区中可读数据的起始地址
        const char* peek() const {
            return begin() + readerIndex_;
        }

        //复位操作
        void retrieve(size_t len){
            //一次没有全部读完可读数据,那么移动readerIndex_
            if(len < readableBytes()){
                readerIndex_ += len;
            } else {
                //一次把全部数据读完了
                retrieveAll();
            }
        }
        //如果缓冲区中的数据被读完了那就置位
        void retrieveAll(){
            readerIndex_ = kCheapPrepend;
            writerIndex_ = kCheapPrepend;
        }

        //将onMessage函数上报的Buffer数据，转成string类型的数据返回
        std::string retrieveAllAsString(){
            return retrieveAsString(readableBytes());
        }
        std::string retrieveAsString(size_t len){
            //将可读数据读取到result中然后返回result
            std::string result(peek(),len);
            //因为可读数据被读取到result里了所以需要将缓冲区置位
            retrieve(len);
            return result;
        }

        void cleanSpareSpace(){
            if(readerIndex_ - 8 != 0){
                size_t readable = readableBytes();
                std::copy(begin() + readerIndex_,
                          begin() + writerIndex_,
                          begin() + kCheapPrepend);
                readerIndex_ = kCheapPrepend;
                writerIndex_ = readerIndex_ + readable;
            }
        }

        //确保write缓存区还有len个大小，如果不够那就扩容
        void ensureWriteBytes(size_t len){
            if(writableBytes() < len){
                makespace(len);
            }
        }

        //把string类型的字符串转成char但是不会保留'\0'
        void append(const std::string& str){
            append(str.data(),str.size());
        }
        void append(const char* data,size_t len){
            ensureWriteBytes(len);
            //向writerIndex_的位置写入[data,data+len]的数据,writerIndex_后移
            std::copy(data,data + len,beginWrite());
            writerIndex_ += len;
        }

        char* beginWrite(){
            return begin() + writerIndex_;
        }

        const char* beginWrite() const {
            return begin() + writerIndex_;
        }

        ssize_t readfd(int fd,int* saveErrno);


    private:

        char* begin(){
            return &(*buffer_.begin());
        }

        const char* begin() const {
            return &(*buffer_.begin());
        }
        /* 扩容操作
         * kCheapPrepend | reader | writer
         * prependableBytes() | reader | writer
         * 可能因为reader的空间被读了一部分readerIndex_会后移，因此前面产生了一部分的空闲区，为了避免浪费所以将下标前移空闲位置大小
         */
        void makespace(int len){
            if(writableBytes() + readerIndex_ < len + kCheapPrepend){
                buffer_.resize(writerIndex_ + len);
            } else {
                size_t readable = readableBytes();
                std::copy(begin() + readerIndex_,
                          begin() + writerIndex_,
                          begin() + kCheapPrepend);
                readerIndex_ = kCheapPrepend;
                writerIndex_ = readerIndex_ + readable;
            }

        }

        std::vector<char> buffer_;
        size_t readerIndex_;
        size_t writerIndex_;
    };
}


#endif //NET_LIB_BUFFER_H
