/**
 * File: exception_handler.hpp
 * Project: engine
 * File Created: 2023-05-01 19:57:12
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-04 14:33:03
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#ifndef ENGINE_CORE_EXCEPTION_HANDLER_HPP
#define ENGINE_CORE_EXCEPTION_HANDLER_HPP

namespace vmk {

class Exception_Handler : private std::runtime_error {
  public:
    explicit Exception_Handler(std::string message);
    explicit Exception_Handler(const std::ostringstream& stream_message);
    ~Exception_Handler() override = default;

    [[nodiscard]] const std::string& get_message() const;

    Exception_Handler(const Exception_Handler&) = default;
    Exception_Handler(Exception_Handler&&) = delete;
    Exception_Handler& operator=(const Exception_Handler&) = default;
    Exception_Handler& operator=(Exception_Handler&&) = delete;

  private:
    std::string m_message;
};

}

#endif // ENGINE_CORE_EXCEPTION_HANDLER_HPP
