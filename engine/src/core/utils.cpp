/**
 * File: utils.cpp
 * Project: engine
 * File Created: 2023-05-06 20:19:35
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-06 20:32:05
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#include "core/utils.hpp"

#include <algorithm>

namespace vmk {

void
Utils::press_any_key_to_quit()
{
    std::cout << "Press any key to quit...";
    _getch();
}

std::string&
Utils::to_upper(std::string& string)
{
    std::transform(string.begin(), string.end(), string.begin(), ::toupper);
    return string;
}

std::string&
Utils::to_lower(std::string& string)
{
    std::transform(string.begin(), string.end(), string.begin(), ::tolower);
    return string;
}

u32
Utils::to_u32(const std::string& value, std::ios_base& (*format)(std::ios_base&))
{
    try {
        return convert_to_type<u32>(value, format);
    }
    catch (...) {
        return 0;
    }
}

}
