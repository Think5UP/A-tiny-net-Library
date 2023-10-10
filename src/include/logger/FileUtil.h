#ifndef FILEUTIL_H_
#define FILEUTIL_H_

#include <stdio.h>

#include <string>

class FileUtil {
 public:
  explicit FileUtil(std::string &fileName);
  ~FileUtil();

  void append(const char *data, size_t);

  void flush();

  off_t writtenBytes() const { return writtenBytes_; }

 private:
  size_t write(const char *data, size_t len);

  FILE *fp_;
  char buffer_[64 * 1024];  // 文件的缓冲区
  off_t writtenBytes_;      // 文件的偏移量
};

#endif  // !FILEUTIL_H_
