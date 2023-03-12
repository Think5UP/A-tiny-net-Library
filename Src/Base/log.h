////
//// Created by root on 2/15/23.
////
//
//#ifndef NET_LIB_LOG_H
//#define NET_LIB_LOG_H
//
//
//#include <string>
//#include <vector>
//#include <fstream>
//#include <iostream>
//#include <memory>
//#include <sstream>
//
//namespace net_lib{
//
//    class LogLevel{
//    public:
//        enum Level{
//            UNKNOW = 0,
//            DEBUG = 1,
//            INFO = 2,
//            FATAL = 3,
//            WARNING = 4,
//            ERROR = 5
//        };
//    };
//
//    class LogEvent{
//    public:
//        typedef std::shared_ptr<LogEvent> ptr;
//        LogEvent(std::string name,net_lib::LogLevel::Level level,
//                 std::string filename,int line,int64_t elapse,
//                 uint64_t threadId,int64_t time,std::stringstream ss)
//                 : m_name(name),m_filename(filename),m_line(line),
//                 m_elapse(elapse),m_threadID(threadId),m_time(time){}
//
//
//        std::string getNae() const {return m_name;}
//        net_lib::LogLevel::Level getLevel() const {return m_level;}
//        std::string getFilename() const {return m_filename;}
//        int getLine()const { return m_line; }
//        int64_t getElapse() const {return m_elapse;}
//        uint64_t geThreadID() const {return m_threadID;}
//        int64_t getTime() const {return m_time;}
//        std::string getContent() const {return m_ss.str();}
//
//        const std::stringstream &getSS() const {return m_ss;}
//        const std::string& getLoggerName() const {return m_loggerName;}
//    private:
//        std::string m_name;
//        LogLevel::Level m_level;
//        std::string m_filename;
//        int m_line;
//        int64_t m_elapse;
//        uint64_t m_threadID;
//        int64_t m_time;
//        std::stringstream m_ss;
//        std::string m_loggerName;
//    };
//
//    class Logger{
//
//    };
//
//    class LogFormatter{
//    public:
//        typedef std::shared_ptr<LogFormatter> ptr;
//        LogFormatter(const std::string& pattern = "%d{%y-%m-%d }");
//        void init();
//
//        std::string getPattern() const {return m_pattern;}
//        bool isError(){return m_error;}
//
//    public:
//        class FormatItem{
//        public:
//            typedef std::shared_ptr<FormatItem> ptr;
//            virtual ~FormatItem();
//        };
//
//    private:
//        std::string m_pattern;
//        std::vector<FormatItem> m_Items;
//        bool m_error = false;
//    };
//
//    class LogAppender{
//    public:
//
//
//    };
//
//    class StdAppender : public LogAppender{
//
//    };
//
//    class FileAppender: public LogAppender{
//
//    };
//
//
//}
//
//
//
//
//#endif //NET_LIB_LOG_H
