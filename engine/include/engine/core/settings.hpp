/**
 * File: settings.hpp
 * Project: engine
 * File Created: 2023-05-06 19:53:06
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-06 20:13:12
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#ifndef ENGINE_CORE_SETTINGS_HPP
#define ENGINE_CORE_SETTINGS_HPP

#include "engine/core/singleton.hpp"

namespace vmk {

class Settings : public Singleton {
  public:
    static Settings* get();

    Settings();
    ~Settings() override;

    void set_rng_seed(u64 seed);
    void set_windowed_mode(bool is_windowed);
    void set_stat_logging(bool enable);

    [[nodiscard]] f64 get_physics_step_seconds() const;
    [[nodiscard]] bool is_windowed_mode() const;
    [[nodiscard]] bool is_stat_logging_enable() const;
    [[nodiscard]] std::string show_summary() const;

    Settings(const Settings&) = default;
    Settings(Settings&&) = delete;
    Settings& operator=(const Settings&) = default;
    Settings& operator=(Settings&&) = delete;

  private:
    u32 m_physics_update_rate;
    bool m_windowed_mode;
    u64 m_rng_seed;
    bool m_enable_stats_log;
};

}

#endif // ENGINE_CORE_SETTINGS_HPP
