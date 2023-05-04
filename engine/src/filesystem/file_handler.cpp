/**
 * File: file_handler.cpp
 * Project: engine
 * File Created: 2023-05-04 17:39:22
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-04 18:01:47
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#include "filesystem/file_handler.hpp"

#include "core/exception_handler.hpp"

namespace vmk {

File_Handler::File_Handler(std::string filepath, bool log_exceptions_to_file)
  : m_filepath(std::move(filepath))
  , m_log_exceptions_to_file(log_exceptions_to_file)
{
}

File_Handler::~File_Handler()
{
    if (m_file_stream.is_open()) {
        m_file_stream.close();
    }
}

void
File_Handler::throw_error(std::string message) const
{
    throw Exception_Handler("File [" + m_filepath + "] " + std::move(message), m_log_exceptions_to_file);
}

void
File_Handler::throw_error(const std::ostringstream& message) const
{
    throw_error(message.str());
}

}
