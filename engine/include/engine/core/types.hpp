/**
 * File: types.hpp
 * Project: engine
 * File Created: 2023-05-01 19:09:35
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-01 19:48:59
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#pragma once

#include <cstdint>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using f32 = float;
using f64 = double;

enum Return_Code : i32 {
    RC_OK = 0,
    RC_ERROR = 1,
};
