/**
 * File: block_process.cpp
 * Project: engine
 * File Created: 2023-05-02 21:10:08
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-02 21:25:11
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#include "thread/block_process.hpp"

namespace vmk {

Block_Process::Block_Process(const std::string& name)
  : m_mutex(CreateMutex(nullptr, FALSE, name.c_str()))
{
}

Block_Process::~Block_Process()
{
    CloseHandle(m_mutex);
}

bool
Block_Process::is_blocked() const
{
    return (m_mutex == nullptr || GetLastError() == ERROR_ALREADY_EXISTS);
}

}
