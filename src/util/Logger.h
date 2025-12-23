//
// Created by augus on 23.12.2025.
//

#ifndef SCHACHENGINE_LOGGER_H
#define SCHACHENGINE_LOGGER_H

#endif //SCHACHENGINE_LOGGER_H
#pragma once

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

namespace Chess {
    enum class Level {
        Info,
        Warn,
        Error
    };

    inline const char* levelToString(Level lvl) {
        switch (lvl) {
            case Level::Info:  return "INFO";
            case Level::Warn:  return "WARN";
            case Level::Error: return "ERROR";
            default:           return "UNKNOWN";
        }
    }

    inline std::string timestamp() {
        using namespace std::chrono;

        auto now = system_clock::now();
        auto time = system_clock::to_time_t(now);
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

        std::tm tm{};
#if defined(_WIN32)
        localtime_s(&tm, &time);
#else
        localtime_r(&time, &tm);
#endif

        std::ostringstream oss;
        oss << std::put_time(&tm, "%H:%M:%S")
            << '.' << std::setfill('0') << std::setw(3) << ms.count();

        return oss.str();
    }

    inline void log(Level lvl,
                    const std::string& msg,
                    const char* file,
                    int line) {

        std::cout
            << "[" << timestamp() << "] "
            << "[" << levelToString(lvl) << "] "
            << "[" << file << ":" << line << "] "
            << msg
            << std::endl;
    }
// #define LOG_INFO(msg)  Chess::log(Chess::Level::Info,  msg, __FILE__, __LINE__)
// #define LOG_WARN(msg)  Chess::log(Chess::Level::Warn,  msg, __FILE__, __LINE__)
// #define LOG_ERROR(msg) Chess::log(Chess::Level::Error, msg, __FILE__, __LINE__)
#define LOG_INFO(msg)  do { \
std::ostringstream _oss; \
_oss << msg; \
Chess::log(Chess::Level::Info, _oss.str(), __FILE__, __LINE__); \
} while(0)

#define LOG_WARN(msg)  do { \
std::ostringstream _oss; \
_oss << msg; \
Chess::log(Chess::Level::Warn, _oss.str(), __FILE__, __LINE__); \
} while(0)

#define LOG_ERROR(msg) do { \
std::ostringstream _oss; \
_oss << msg; \
Chess::log(Chess::Level::Error, _oss.str(), __FILE__, __LINE__); \
} while(0)
}