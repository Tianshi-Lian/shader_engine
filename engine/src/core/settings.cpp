/**
 * File: settings.cpp
 * Project: engine
 * File Created: 2023-05-06 19:58:06
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-07 15:28:52
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#include "core/settings.hpp"

#include "core/exception_handler.hpp"

namespace {
vmk::Settings* s_settings_inst = nullptr;
}

namespace vmk {

Settings*
Settings::get()
{
    if (s_settings_inst == nullptr) {
        throw Exception_Handler(__FUNCTION__ + std::string(" failed, Settings has not been constructed."));
    }
    return s_settings_inst;
}

Settings::Settings()
  : Singleton(Type::Settings)
  , m_physics_update_rate(100)
  , m_windowed_mode(false)
  , m_rng_seed(0)
  , m_enable_stats_log(false)
{
    s_settings_inst = this;
}

Settings::~Settings()
{
    s_settings_inst = nullptr;
}

void
Settings::set_rng_seed(u64 seed)
{
    m_rng_seed = seed;
}

void
Settings::set_windowed_mode(bool is_windowed)
{
    m_windowed_mode = is_windowed;
}

void
Settings::set_stat_logging(bool enable)
{
    m_enable_stats_log = enable;
}

f64
Settings::get_physics_step_seconds() const
{
    return (1.0 / static_cast<f64>(m_physics_update_rate));
}

bool
Settings::is_windowed_mode() const
{
    return m_windowed_mode;
}

bool
Settings::is_stat_logging_enable() const
{
    return m_enable_stats_log;
}

std::string
Settings::show_summary() const
{
    std::ostringstream out_stream;
    out_stream << "Game Settings:\n";

    out_stream << "    Seed Value: " << m_rng_seed << "\n";
    out_stream << "    Display Mode: " << (m_windowed_mode ? "Windowed" : "Fullscreen") << "\n";
    out_stream << "    Physics Refresh: " << m_physics_update_rate << " Hz\n";
    out_stream << "    Stats Logging: " << (m_enable_stats_log ? "Enabled" : "Disabled") << "\n";

    return out_stream.str();
}

}
