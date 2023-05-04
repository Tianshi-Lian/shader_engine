/**
 * File: exception_handler.cpp
 * Project: engine
 * File Created: 2023-05-01 19:57:50
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-04 18:14:23
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#include "core/exception_handler.hpp"

#include "debug/logger.hpp"

namespace vmk {

Logger* Exception_Handler::s_logger = nullptr;

Exception_Handler::Exception_Handler(std::string message, bool log_to_file)
  : std::runtime_error(message)
  , m_message(std::move(message))
{
    if (log_to_file && (s_logger != nullptr)) {
        s_logger->log(Logger::Log_Level::L_ERROR, m_message);
    }
}

Exception_Handler::Exception_Handler(const std::ostringstream& stream_message, bool log_to_file)
  : std::runtime_error(stream_message.str())
  , m_message(stream_message.str())
{
    if (log_to_file && (s_logger != nullptr)) {
        s_logger->log(Logger::Log_Level::L_ERROR, m_message);
    }
}

void
Exception_Handler::set_logger(Logger* logger)
{
    s_logger = logger;
}

const std::string&
Exception_Handler::get_message() const
{
    return m_message;
}

}
