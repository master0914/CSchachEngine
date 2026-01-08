//
// Created by augus on 23.12.2025.
//

#ifndef SCHACHENGINE_LOGGER_H
#define SCHACHENGINE_LOGGER_H
#include <filesystem>

#endif //SCHACHENGINE_LOGGER_H
#pragma once

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

namespace Chess {
    static constexpr const char* RESET = "\033[0m";
    static constexpr const char* RED = "\033[31m";
    static constexpr const char* GREEN = "\033[32m";
    static constexpr const char* YELLOW = "\033[33m";
    static constexpr const char* BRIGHT_RED = "\033[91m";
    static constexpr const char* BRIGHT_GREEN = "\033[92m";
    static constexpr const char* BRIGHT_YELLOW = "\033[93m";

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
    inline const char* levelToColorCode(Level lvl) {
        const char* levelColor = "";
        switch (lvl) {
            case Level::Info:
                levelColor = BRIGHT_GREEN;
                break;
            case Level::Warn:
                levelColor = BRIGHT_YELLOW;
                break;
            case Level::Error:
                levelColor = BRIGHT_RED;
                break;
        }
        return levelColor;
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
        std::filesystem::path filepath(file);
        std::string filename = filepath.filename().string(); // nur Dateiname
        std::cout
            << "[" << timestamp() << "] "
            << "[" << levelToString(lvl) << "] "
            << "[" << filename << ":" << line << "] "
            << msg
            << std::endl;
    }
}
#ifdef CHESS_ENABLE_LOGGING

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

#else

#define LOG_INFO(msg)  ((void)0)
#define LOG_WARN(msg)  ((void)0)
#define LOG_ERROR(msg) ((void)0)

#endif

#if LOG_ENABLE_MOVEGEN
#define LOG_MOVEGEN(msg) LOG_INFO(msg)
#else
#define LOG_MOVEGEN(msg) ((void)0)
#endif

#if LOG_ENABLE_SEARCH
#define LOG_SEARCH(msg) LOG_INFO(msg)
#else
#define LOG_SEARCH(msg) ((void)0)
#endif

#if LOG_ENABLE_UI
#define LOG_UI(msg) LOG_INFO(msg)
#else
#define LOG_UI(msg) ((void)0)
#endif

#if LOG_ENABLE_RENDER
#define LOG_RENDER(msg) LOG_INFO(msg)
#else
#define LOG_RENDER(msg) ((void)0)
#endif

#if LOG_ENABLE_BOARD
#define LOG_BOARD(msg) LOG_INFO(msg)
#else
#define LOG_BOARD(msg) ((void)0)
#endif