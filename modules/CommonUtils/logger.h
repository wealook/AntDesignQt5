#pragma once

#ifdef _MSC_VER
#pragma warning(disable: 4819) // disable warning 4819
#endif

#include <sstream>
#include <functional>
#include <thread>

namespace wl {

    class Logger {
    public:
        typedef std::function<void(int, const char *)> ExternalSink;

        virtual ~Logger() {}

        enum LogTarget {
            eLogNone = 0,
            eLogFile = 1,
            eLogSys = 2,
            eLogMSVC = 4
        };

        enum LogLevel {
            eLogTrace = 0,
            eLogDebug = 1,
            eLogInfo = 2,
            eLogWarn = 3,
            eLogError = 4,
            eLogCritical = 5,
            eLogOff = 6
        };

        static Logger &instance();

        void init(const std::string &path = "",
                  LogTarget target = static_cast<LogTarget>( static_cast<int>(LogTarget::eLogFile) |
                                                             static_cast<int>(LogTarget::eLogSys)),
                  LogLevel level = LogLevel::eLogDebug, const std::string &tagName = "logs");

        void logMessage(int level, const std::string &message);

        void shutdown();

        void setExternalSink(ExternalSink sink) {
            externalSink_ = sink;
        }

        std::thread::id threadIdMain() const {
            return threadIdMain_;
        }

        std::thread::id threadIdCurrent() const;

        std::string defaultFolder() const {
            return logFolder_;
        }

        std::string logFilePath() const {
            return logFilePath_;
        }

    protected:
        Logger() : inited_(false), externalSink_(nullptr) {
            threadIdMain_ = threadIdCurrent();
        }

        bool inited_;
        ExternalSink externalSink_;
        std::thread::id threadIdMain_;
        std::string logFolder_;
        std::string logFilePath_;
    };

}


#define LOG_MESSAGE(level, x) \
    do { \
        std::stringstream out; \
        out << x; \
        wl::Logger::instance().logMessage(level, "[" + std::string(__FUNCTION__) + ":"+ std::to_string(__LINE__)+ "] " + out.str()); \
    } while(0); \



#define LOG_INFO(x) LOG_MESSAGE(wl::Logger::eLogInfo, x)
#define LOG_DETAIL(x) LOG_MESSAGE(wl::Logger::eLogDebug, x)
#define LOG_WARN(x) LOG_MESSAGE(wl::Logger::eLogWarn, x)
#define LOG_ERROR(x) LOG_MESSAGE(wl::Logger::eLogError, x)
#define LOG_NOTICE(x) LOG_MESSAGE(wl::Logger::eLogCritical, x)
#define IN_MAINTHREAD() (wl::Logger::instance().threadIdCurrent() == wl::Logger::instance().threadIdMain())
