/**
 * File: block_process.hpp
 * Project: engine
 * File Created: 2023-05-02 21:10:00
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-04 14:37:11
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#ifndef ENGINE_THREAD_BLOCK_PROCESS_HPP
#define ENGINE_THREAD_BLOCK_PROCESS_HPP

#include "engine/core/win32.hpp"

namespace vmk {

class Block_Process {
  public:
    explicit Block_Process(const std::string& name);
    ~Block_Process();

    [[nodiscard]] bool is_blocked() const;

    Block_Process(const Block_Process&) = default;
    Block_Process(Block_Process&&) = delete;
    Block_Process& operator=(const Block_Process&) = default;
    Block_Process& operator=(Block_Process&&) = delete;

  private:
    HANDLE m_mutex;
};

} // namespace vmk

#endif // ENGINE_THREAD_BLOCK_PROCESS_HPP
