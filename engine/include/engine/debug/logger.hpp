/**
 * File: logger.hpp
 * Project: engine
 * File Created: 2023-05-04 14:39:15
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-04 17:22:18
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#ifndef ENGINE_DEBUG_LOGGER_HPP
#define ENGINE_DEBUG_LOGGER_HPP

#include "engine/core/singleton.hpp"

#include "engine/core/win32.hpp"

namespace vmk {
class Logger final : public Singleton {
  public:
    enum class Log_Level : u32 {
        L_INFO = 0,
        L_WARNING,
        L_ERROR,
        COUNT
    };

    explicit Logger(std::string log_filepath);
    ~Logger() override;

    void log(Log_Level level, const std::string& message);
    void log(Log_Level level, const std::ostringstream& message);
    void log(Log_Level level, const char* message);

    Logger(const Logger&) = default;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = default;
    Logger& operator=(Logger&&) = delete;

  private:
    std::string m_log_filepath;

    std::array<std::string, static_cast<i32>(Log_Level::COUNT)> m_log_types;
    u32 m_log_level_max_length;

    CRITICAL_SECTION m_critical_section;
};
}

#endif // ENGINE_DEBUG_LOGGER_HPP
