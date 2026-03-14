#pragma once

#include <format>
#include <string>
#include <string_view>
#include <utility>

namespace eldrun::core
{
    enum class LogLevel
    {
        Info,
        Warning,
        Error
    };

    void log(LogLevel level, std::string_view message);

    inline void log_info(std::string_view message)
    {
        log(LogLevel::Info, message);
    }

    inline void log_warning(std::string_view message)
    {
        log(LogLevel::Warning, message);
    }

    inline void log_error(std::string_view message)
    {
        log(LogLevel::Error, message);
    }

    template <typename... Args>
    void log_info(std::format_string<Args...> fmt, Args&&... args)
    {
        log(LogLevel::Info, std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void log_warning(std::format_string<Args...> fmt, Args&&... args)
    {
        log(LogLevel::Warning, std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void log_error(std::format_string<Args...> fmt, Args&&... args)
    {
        log(LogLevel::Error, std::format(fmt, std::forward<Args>(args)...));
    }
}