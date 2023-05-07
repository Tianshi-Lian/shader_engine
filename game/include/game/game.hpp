/**
 * File: game.hpp
 * Project: game
 * File Created: 2023-05-07 18:49:09
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-07 18:50:42
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include "engine/engine.hpp"

namespace vmk {

class Game : public Engine {
  public:
    Game() = default;
    ~Game() override = default;

    Game(const Game&) = default;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = default;
    Game& operator=(Game&&) = delete;
};

}

#endif // GAME_GAME_HPP
