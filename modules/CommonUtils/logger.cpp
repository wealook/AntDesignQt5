#include "logger.h"
#include "sys_utils.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/msvc_sink.h"
#include "spdlog/async.h"

#include<filesystem>

#if defined(ANDROID)
#include "spdlog/sinks/android_sink.h"
#endif

#include <iostream>
#include <regex>

using namespace wl;

namespace wl {

    Logger &Logger::instance() {
        static Logger logger;
        return logger;
    }

    void Logger::shutdown() {
        inited_ = false;
        spdlog::shutdown();
    }

    std::thread::id Logger::threadIdCurrent() const {
        return std::this_thread::get_id();
    }

    void Logger::init(const std::string &path, LogTarget target, LogLevel level, const std::string &tagName) {
        if (inited_)
            return;

        spdlog::init_thread_pool(8192, 1);
        std::vector<spdlog::sink_ptr> sinks;

        std::string outFolder;
        if (static_cast<int>(target) & static_cast<int>( LogTarget::eLogFile)) {
            if (path.find("\\") != std::string::npos || path.find("/") != std::string::npos) {
                outFolder = path;
                if (!std::filesystem::exists(outFolder)) {
                    std::filesystem::create_directories(outFolder);
                }
            } else {
#if defined(_WINDOWS)
                std::string defaultFolder = getDefaultFolder() + "/WL";
            if (!std::filesystem::exists(defaultFolder)) {
                std::filesystem::create_directories(defaultFolder);
            }
            defaultFolder = defaultFolder + "/Logs/";
            if (!std::filesystem::exists(defaultFolder)) {
                std::filesystem::create_directories(defaultFolder);
            }
#elif defined(__APPLE__)
                std::string defaultFolder = getDefaultFolder() + "/Logs/";
#elif defined(ARMLINUX) || defined(LINUX_GCC)
                std::string defaultFolder = "/var/log/";
#else
                std::string defaultFolder = getDefaultFolder() + "/";
#endif
                outFolder = defaultFolder + (path.empty() ? "SRSCommon" : path);
                if (!std::filesystem::exists(outFolder)) {
                    std::filesystem::create_directories(outFolder);
                }
            }
            logFolder_ = outFolder;
            outFolder += "/" + tagName + ".log";
            logFilePath_ = outFolder;

            std::regex pattern(tagName + "\.(\\d)\.log");
            for (auto const &dir_entry: std::filesystem::directory_iterator(logFolder_)) {
                try {
                    std::smatch result;
                    std::string str = dir_entry.path().filename().string();
                    bool res = std::regex_match(str, result, pattern);
                    if (res) {
                        if (std::stoi(result.str(1)) > 100) {
                            std::filesystem::remove(dir_entry.path());
                        }
                    }
                } catch (std::exception &e) {
                    std::cout << "log init,remove old file error:" << dir_entry.path() << "," << e.what() << std::endl;
                }
            }
            auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(outFolder, 1024 * 1024 * 5, 3);
            sinks.push_back(rotating_sink);
        }

        if (static_cast<int>(target) & static_cast<int>(LogTarget::eLogSys)) {
#if defined(_WINDOWS)
            //auto sys_sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
        auto sys_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
#elif defined(ANDROID)
            auto sys_sink = std::make_shared<spdlog::sinks::android_sink_mt>(tagName);
#else
            auto sys_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
#endif
            sinks.push_back(sys_sink);
        }

        if (static_cast<int>(target) & static_cast<int>(LogTarget::eLogMSVC)) {
#if defined(_WINDOWS)
            auto sys_sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
        sinks.push_back(sys_sink);
#endif
        }

        auto logger = std::make_shared<spdlog::async_logger>("logger",
                                                             sinks.begin(),
                                                             sinks.end(),
                                                             spdlog::thread_pool(),
                                                             spdlog::async_overflow_policy::block);
        //spdlog::register_logger(logger);
        spdlog::set_default_logger(logger);
        spdlog::set_level(static_cast<spdlog::level::level_enum>(level));
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%f] %^[%l]%$ [pid=%P tid=%t] %v");
        spdlog::flush_on(static_cast<spdlog::level::level_enum>(level));

        spdlog::info("SRSLogger initialized...");
        if (static_cast<int>(target) & static_cast<int>(LogTarget::eLogFile))
            spdlog::info("File logging was enabled, log was saved at: {}", outFolder);
        inited_ = true;
    }

    void Logger::logMessage(int level, const std::string &message) {
        spdlog::log(static_cast<spdlog::level::level_enum>(level), message.c_str());
        if (externalSink_)
            externalSink_(level, message.c_str());
    }
}
