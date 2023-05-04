/**
 * File: singleton.cpp
 * Project: engine
 * File Created: 2023-05-04 14:11:20
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-04 18:04:08
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#include "core/singleton.hpp"

#include "core/exception_handler.hpp"

namespace {

struct Singleton_Info {
    std::string singleton_name;
    bool is_constructed{};

    explicit Singleton_Info(std::string name)
      : singleton_name(std::move(name))
    {
    }
};

std::array<Singleton_Info, static_cast<size_t>(vmk::Singleton::Type::COUNT)> s_singletons = { Singleton_Info("Logger") };

}

namespace vmk {

Singleton::Singleton(Singleton::Type type)
  : m_type(type)
{
    try {
        u32 new_singleton_id = static_cast<u32>(type);

        if (!s_singletons.at(new_singleton_id).is_constructed) {
            // Singletons are chained dependents
            for (u32 i = 0; i < new_singleton_id; ++i) {
                if (!s_singletons.at(i).is_constructed) {
                    throw Exception_Handler(
                        s_singletons.at(i).singleton_name + " must be constructed before " +
                        s_singletons.at(new_singleton_id).singleton_name
                    );
                }
            }
            s_singletons.at(new_singleton_id).is_constructed = true;
        }
        else {
            throw Exception_Handler(s_singletons.at(new_singleton_id).singleton_name + " can only be constructed once");
        }
    }
    catch (const std::exception& e) {
        std::ostringstream str_stream;
        str_stream << __FUNCTION__ << "Invalid Singleton::Type specified: " << static_cast<u32>(type);
        throw Exception_Handler(str_stream);
    }
}

Singleton::~Singleton()
{
    s_singletons.at(static_cast<u32>(m_type)).is_constructed = false;
}

}
