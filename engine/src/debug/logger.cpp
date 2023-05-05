/**
 * File: logger.cpp
 * Project: engine
 * File Created: 2023-05-04 14:45:55
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-05 18:10:14
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#include "debug/logger.hpp"

#include "filesystem/text_file_writer.hpp"
#include "thread/block_thread.hpp"

namespace {
vmk::Logger* s_logger_inst = nullptr;
}

namespace vmk {

Logger::Logger(std::string log_filepath)
  : Singleton(Type::Logger)
  , m_log_filepath(std::move(log_filepath))
  , m_log_level_max_length(0)
  , m_critical_section()
{
    m_log_types.at(static_cast<u32>(Log_Level::L_INFO)) = "Info";
    m_log_types.at(static_cast<u32>(Log_Level::L_WARNING)) = "Warning";
    m_log_types.at(static_cast<u32>(Log_Level::L_ERROR)) = "Error";

    for (const std::string& level : m_log_types) {
        if (m_log_level_max_length < level.size()) {
            m_log_level_max_length = static_cast<u32>(level.size());
        }
    }

    InitializeCriticalSection(&m_critical_section);
    Block_Thread block_thread(m_critical_section);

    Text_File_Writer file(m_log_filepath, false, false);

    s_logger_inst = this;
}

Logger::~Logger()
{
    s_logger_inst = nullptr;
    DeleteCriticalSection(&m_critical_section);
}

void
Logger::log(Log_Level level, const std::string& message)
{
    log(level, message.c_str());
}

void
Logger::log(Log_Level level, const std::ostringstream& message)
{
    log(level, message.str().c_str());
}

void
Logger::log(Log_Level level, const char* message)
{
    if (s_logger_inst == nullptr) {
        std::cout << "Logger has been used without being initialized. Failed to log: " << message << std::endl;
        return;
    }

    Block_Thread block_thread(s_logger_inst->m_critical_section);

    std::ostringstream str_stream;

    SYSTEMTIME time;
    GetLocalTime(&time);

    // Timestamp
    str_stream << time.wYear << "." << std::setfill('0') << std::setw(2) << time.wMonth << "." << std::setfill('0')
               << std::setw(2) << time.wDay << " " << std::setfill(' ') << std::setw(2) << time.wHour << ":"
               << std::setfill('0') << std::setw(2) << time.wMinute << ":" << std::setfill('0') << std::setw(2) << time.wSecond
               << "." << std::setfill('0') << std::setw(3) << time.wMilliseconds;

    // Log level
    str_stream << " [" << s_logger_inst->m_log_types.at(static_cast<u32>(level)) << std::setfill(' ')
               << std::setw(static_cast<i32>(s_logger_inst->m_log_level_max_length)) << "] ";

    // Write to console
    str_stream << message;
    std::cout << str_stream.str() << std::endl;

    // Write to log file
    try {
        Text_File_Writer file(s_logger_inst->m_log_filepath, true, false);
        file.write(str_stream.str());
    }
    catch (...) {
        // Suppressed.
    }
}

}
