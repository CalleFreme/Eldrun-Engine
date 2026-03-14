#include "eldrun/core/log.hpp"

#include <iostream>

namespace eldrun::core
{
    namespace
    {
        const char* to_string(const LogLevel level)
        {
            switch (level)
            {
            case LogLevel::Info:
                return "INFO";
            case LogLevel::Warning:
                return "WARN";
            case LogLevel::Error:
                return "ERROR";
            default:
                return "UNKNOWN";
            }
        }
    }

    void log(const LogLevel level, const std::string_view message)
    {
        std::cout << "[Eldrun][" << to_string(level) << "] " << message << '\n';
    }
}