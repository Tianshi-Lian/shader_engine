/**
 * File: types.hpp
 * Project: engine
 * File Created: 2023-05-01 19:09:35
 * Author: Rob Graham (robgrahamdev@gmail.com)
 * Last Modified: 2023-05-07 17:37:16
 * ------------------
 * Copyright 2023 Rob Graham
 * ==================
 */

#ifndef ENGINE_CORE_TYPES_HPP
#define ENGINE_CORE_TYPES_HPP

#include <cstdint>
#include <glm/glm.hpp>

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

using v1 = glm::f32vec1;
using v2 = glm::f32vec2;
using v3 = glm::f32vec3;
using v4 = glm::f32vec4;

using v1f = v1;
using v2f = v2;
using v3f = v3;
using v4f = v4;

using v1i = glm::ivec1;
using v2i = glm::ivec2;
using v3i = glm::ivec3;
using v4i = glm::ivec4;

using v1u = glm::uvec1;
using v2u = glm::uvec2;
using v3u = glm::uvec3;
using v4u = glm::uvec4;

using m2 = glm::f32mat2;
using m3 = glm::f32mat3;
using m4 = glm::f32mat4;

using m2f = glm::f32mat2;
using m3f = glm::f32mat3;
using m4f = glm::f32mat4;

enum Return_Code : i32 {
    RC_OK = 0,
    RC_ERROR = 1,
};

#endif // ENGINE_CORE_TYPES_HPP
