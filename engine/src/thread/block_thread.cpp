/**
 * File: block_thread.cpp
 * Project: engine
 * File Created: 2023-05-02 21:22:40
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-02 21:24:55
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#include "thread/block_thread.hpp"

namespace vmk {

Block_Thread::Block_Thread(CRITICAL_SECTION& critical_section)
  : m_critical_section(&critical_section)
{
    EnterCriticalSection(m_critical_section);
}

Block_Thread::~Block_Thread()
{
    LeaveCriticalSection(m_critical_section);
}

}
