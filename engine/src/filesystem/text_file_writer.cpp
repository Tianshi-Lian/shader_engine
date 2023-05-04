/**
 * File: text_file_writer.cpp
 * Project: engine
 * File Created: 2023-05-04 17:50:15
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-04 18:00:21
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#include "filesystem/text_file_writer.hpp"

namespace vmk {

Text_File_Writer::Text_File_Writer(std::string filepath, bool append, bool log_exceptions_to_file)
  : File_Handler(std::move(filepath), log_exceptions_to_file)
{
    m_file_stream.open(filepath.c_str(), std::ios_base::out | (append ? std::ios_base::app : std::ios_base::trunc));

    if (!m_file_stream.is_open()) {
        throw_error(__FUNCTION__ + std::string(" can not open file for writing"));
    }
}

void
Text_File_Writer::write(const std::string& value)
{
    m_file_stream << value;
}

}
