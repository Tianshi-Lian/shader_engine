/**
 * File: exception_handler.cpp
 * Project: engine
 * File Created: 2023-05-01 19:57:50
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-04 18:02:33
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#include "core/exception_handler.hpp"

namespace vmk {

Exception_Handler::Exception_Handler(std::string message, bool log_to_file)
  : std::runtime_error(message)
  , m_message(std::move(message))
{
    (void)log_to_file;
}

Exception_Handler::Exception_Handler(const std::ostringstream& stream_message, bool log_to_file)
  : std::runtime_error(stream_message.str())
  , m_message(stream_message.str())
{
    (void)log_to_file;
}

const std::string&
Exception_Handler::get_message() const
{
    return m_message;
}

}
