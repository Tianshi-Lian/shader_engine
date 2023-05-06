/**
 * File: utils.hpp
 * Project: engine
 * File Created: 2023-05-06 20:16:19
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-06 20:32:10
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#ifndef ENGINE_CORE_UTILS_HPP
#define ENGINE_CORE_UTILS_HPP

#include "engine/core/exception_handler.hpp"
#include "engine/debug/logger.hpp"

namespace vmk {

class Utils {

  public:
    static void press_any_key_to_quit();

    static std::string& to_upper(std::string& string);
    static std::string& to_lower(std::string& string);

    static u32 to_u32(const std::string& value, std::ios_base& (*format)(std::ios_base&) = std::dec);

  private:
    template<typename T>
    static T convert_to_type(const std::string& value, std::ios_base& (*format)(std::ios_base&))
    {
        T output;
        std::istringstream input(value);
        input >> format >> output;

        if (!input) {
            std::ostringstream str_stream;
            str_stream << __FUNCTION__ << " failed to convert " << value << " to type " << typeid(output).name();
            throw Exception_Handler(str_stream);
        }

        char first_char = 0;
        if (input.get(first_char)) {
            std::ostringstream str_stream;
            str_stream << __FUNCTION__ << " conversion of " << value << " to type " << typeid(output).name() << " = " << output;
            Logger::log(Logger::Log_Level::L_WARNING, str_stream);
        }
        return output;
    }
};

}

#endif // ENGINE_CORE_UTILS_HPP
