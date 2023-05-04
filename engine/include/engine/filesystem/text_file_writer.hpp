/**
 * File: text_file_writer.hpp
 * Project: engine
 * File Created: 2023-05-04 17:47:02
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-04 17:51:37
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#ifndef ENGINE_FILESYSTEM_TEXT_FILE_WRITER_HPP
#define ENGINE_FILESYSTEM_TEXT_FILE_WRITER_HPP

#include "filesystem/file_handler.hpp"

namespace vmk {

class Text_File_Writer final : public File_Handler {
  public:
    Text_File_Writer(std::string filepath, bool append, bool log_exceptions_to_file = true);

    void write(const std::string& value);
};

}

#endif // ENGINE_FILESYSTEM_TEXT_FILE_WRITER_HPP
