/**
 * File: block_thread.hpp
 * Project: engine
 * File Created: 2023-05-02 21:22:33
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-04 14:37:04
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#ifndef ENGINE_THREAD_BLOCK_THREAD_HPP
#define ENGINE_THREAD_BLOCK_THREAD_HPP

#include "engine/core/win32.hpp"

namespace vmk {

class Block_Thread {
  public:
    explicit Block_Thread(CRITICAL_SECTION& critical_section);
    ~Block_Thread();

    Block_Thread(const Block_Thread&) = default;
    Block_Thread(Block_Thread&&) = delete;
    Block_Thread& operator=(const Block_Thread&) = default;
    Block_Thread& operator=(Block_Thread&&) = delete;

  private:
    CRITICAL_SECTION* m_critical_section;
};

} // namespace vmk

#endif // ENGINE_THREAD_BLOCK_THREAD_HPP
