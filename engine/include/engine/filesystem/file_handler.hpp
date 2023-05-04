/**
 * File: file_handler.hpp
 * Project: engine
 * File Created: 2023-05-04 17:21:33
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-04 17:55:39
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#ifndef ENGINE_FILESYSTEM_FILE_HANDLER_HPP
#define ENGINE_FILESYSTEM_FILE_HANDLER_HPP

#include <fstream>

namespace vmk {

class File_Handler {
  public:
    virtual ~File_Handler();

    File_Handler(const File_Handler&) = delete;
    File_Handler(File_Handler&&) = delete;
    File_Handler& operator=(const File_Handler&) = delete;
    File_Handler& operator=(File_Handler&&) = delete;

  protected:
    File_Handler(std::string filepath, bool log_exceptions_to_file);

    void throw_error(std::string message) const;
    void throw_error(const std::ostringstream& message) const;

    std::fstream m_file_stream;
    std::string m_filepath;
    std::string m_full_filepath;

  private:
    bool m_log_exceptions_to_file;
};

}

#endif // ENGINE_FILESYSTEM_FILE_HANDLER_HPP
