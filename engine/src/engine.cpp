/**
 * File: engine.cpp
 * Project: engine
 * File Created: 2023-05-07 17:50:44
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-07 18:57:24
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#include "engine.hpp"

#include "core/exception_handler.hpp"
#include "core/settings.hpp"
#include "debug/logger.hpp"

namespace {
vmk::Engine* s_engine_inst = nullptr;
}

namespace vmk {

Engine::Engine()
  : Singleton(Type::Engine)
  , m_settings(Settings::get())
  , m_current_type_secs(0)
  , m_previous_time{}
  , m_hwnd(nullptr)
  , m_wnd_class{}
  , m_hinstance(nullptr)
  , m_msg{}
  , m_hdc(nullptr)
{
    s_engine_inst = this;

    LARGE_INTEGER frequency;
    if (QueryPerformanceFrequency(&frequency) == 0) {
        throw Exception_Handler("Hardware does not support high-resolution performance counter");
    }

    m_time_scale_factor = 1.0 / static_cast<f64>(frequency.QuadPart);

    QueryPerformanceCounter(&m_previous_time);

    create_window();
}

Engine::~Engine()
{
    destroy_window();
}

void
Engine::start()
{
    while (true) {
        if (PeekMessage(&m_msg, m_hwnd, 0, 0, PM_REMOVE)) {
            if (m_msg.message == WM_QUIT) {
                break;
            }
            else {
                TranslateMessage(&m_msg);
                DispatchMessage(&m_msg);
            }
        }
        else {
        }
    }
}

void
Engine::create_window()
{
    const auto game_size = m_settings->get_game_size();

    if (!m_settings->get_windowed_mode()) {
        DEVMODE screen_settings;
        memset(&screen_settings, 0, sizeof(screen_settings));

        screen_settings.dmSize = sizeof(screen_settings);
        screen_settings.dmPelsWidth = game_size.x;
        screen_settings.dmPelsHeight = game_size.y;
        screen_settings.dmBitsPerPel = 32;
        screen_settings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        if (ChangeDisplaySettings(&screen_settings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
            std::ostringstream out_stream;
            out_stream << __FUNCTION__ << "failed to switch to full screen " << game_size.x << "x" << game_size.y
                       << ". Running in windowed mode.";
            Logger::log(Logger::Log_Level::L_ERROR, out_stream);
            m_settings->set_windowed_mode(true);
        }
    }

    m_hinstance = GetModuleHandleA(nullptr);

    m_wnd_class.cbSize = sizeof(m_wnd_class);
    m_wnd_class.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC | CS_DBLCLKS;
    m_wnd_class.hInstance = m_hinstance;
    m_wnd_class.hCursor = LoadCursorA(nullptr, IDC_ARROW);
    m_wnd_class.hIcon = LoadIconA(nullptr, IDI_WINLOGO);
    m_wnd_class.hIconSm = LoadIconA(nullptr, IDI_WINLOGO);
    m_wnd_class.lpfnWndProc = window_proc;
    m_wnd_class.lpszClassName = "shader_engine_wnd_class";
    m_wnd_class.cbClsExtra = 0;
    m_wnd_class.cbWndExtra = 0;
    m_wnd_class.hbrBackground = nullptr;
    m_wnd_class.lpszMenuName = nullptr;

    if (!RegisterClassEx(&m_wnd_class)) {
        throw Exception_Handler(__FUNCTION__ + std::string(" win32 failed to register WndClass"));
    }

    DWORD style;
    DWORD style_ex;
    if (m_settings->get_windowed_mode()) {
        style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
        style_ex = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    }
    else {
        style = WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX;
        style_ex = WS_EX_APPWINDOW;
    }

    RECT window_rect;
    window_rect.left = 0;
    window_rect.right = static_cast<i32>(game_size.x);
    window_rect.top = 0;
    window_rect.bottom = static_cast<i32>(game_size.y);

    AdjustWindowRectEx(&window_rect, style, FALSE, style_ex);

    v2i window_size{ window_rect.right - window_rect.left, window_rect.bottom - window_rect.top };

    m_hwnd = CreateWindowEx(
        style_ex,
        "shader_engine_wnd_class",
        "Shader Engine",
        style | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        0,
        0,
        window_size.x,
        window_size.y,
        nullptr,
        nullptr,
        m_hinstance,
        nullptr
    );

    if (m_hwnd == nullptr) {
        throw Exception_Handler(__FUNCTION__ + std::string(" failed to create window"));
    }

    m_hdc = GetDC(m_hwnd);

    if (m_hdc == nullptr) {
        throw Exception_Handler(__FUNCTION__ + std::string(" failed to retrieve device context for window"));
    }

    m_screen_size = v2i{ GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
    if (!m_settings->get_windowed_mode()) {
        i32 pos_x = 0;
        i32 pos_y = 0;

        if (m_screen_size.x > window_size.x) {
            pos_x = (m_screen_size.x - window_size.x) >> 1;
        }
        if (m_screen_size.y > window_size.y) {
            pos_y = (m_screen_size.y - window_size.y) >> 1;
        }

        MoveWindow(m_hwnd, pos_x, pos_y, window_size.x, window_size.y, FALSE);
    }

    ShowWindow(m_hwnd, SW_SHOW);
    SetForegroundWindow(m_hwnd);
    SetFocus(m_hwnd);
    UpdateWindow(m_hwnd);
}

void
Engine::destroy_window()
{
    if (!m_settings->get_windowed_mode()) {
        ChangeDisplaySettings(nullptr, 0);
    }

    if ((m_hwnd != nullptr) && (m_hdc != nullptr)) {
        ReleaseDC(m_hwnd, m_hdc);
        m_hdc = nullptr;
    }

    if (m_hwnd != nullptr) {
        DestroyWindow(m_hwnd);
        m_hwnd = nullptr;
    }

    if (m_hinstance != nullptr) {
        UnregisterClass("shader_engine_wnd_class", m_hinstance);
        m_hinstance = nullptr;
    }
}

bool
Engine::handle_message(u32 msg, WPARAM, LPARAM)
{
    switch (msg) {
        case WM_CLOSE: {
            PostQuitMessage(0);
            return true;
        } break;
        default: {
            return false;
        }
    }
}

LRESULT CALLBACK
Engine::window_proc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
{
    if (s_engine_inst->handle_message(msg, w_param, l_param)) {
        return 0;
    }
    return DefWindowProc(hwnd, msg, w_param, l_param);
}
}
