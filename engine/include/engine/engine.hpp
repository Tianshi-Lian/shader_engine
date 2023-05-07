/**
 * File: engine.hpp
 * Project: engine
 * File Created: 2023-05-07 17:50:37
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-07 18:38:27
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#ifndef ENGINE_ENGINE_HPP
#define ENGINE_ENGINE_HPP

#include "engine/core/singleton.hpp"
#include "engine/core/win32.hpp"

namespace vmk {

class Settings;

class Engine : public Singleton {
  public:
    ~Engine() override;

    void start();

    Engine(const Engine&) = default;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine&) = default;
    Engine& operator=(Engine&&) = delete;

  protected:
    Engine();

    Settings* m_settings;

    f32 m_current_type_secs;

  private:
    void create_window();
    void destroy_window();

    bool handle_message(u32 msg, WPARAM w_param, LPARAM l_param);
    static LRESULT CALLBACK window_proc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);

    LARGE_INTEGER m_previous_time;
    f64 m_time_scale_factor;

    HWND m_hwnd;
    WNDCLASSEX m_wnd_class;
    HINSTANCE m_hinstance;
    MSG m_msg;
    HDC m_hdc;

    v2i m_screen_size;
};

}

#endif // ENGINE_ENGINE_HPP
