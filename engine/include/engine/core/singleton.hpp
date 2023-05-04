/**
 * File: singleton.hpp
 * Project: engine
 * File Created: 2023-05-04 14:08:41
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-04 14:31:33
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#ifndef ENGINE_CORE_SINGLETON_HPP
#define ENGINE_CORE_SINGLETON_HPP

namespace vmk {

class Singleton {
  public:
    enum class Type : u32 {
        Logger = 0,
        COUNT
    };

    virtual ~Singleton();

    Singleton(const Singleton&) = default;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = default;
    Singleton& operator=(Singleton&&) = delete;

  protected:
    explicit Singleton(Type type);

  private:
    Type m_type;
};

}

#endif // ENGINE_CORE_SINGLETON_HPP
