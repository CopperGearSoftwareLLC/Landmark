#pragma once

#include "glm/detail/qualifier.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
using uint8 = glm::uint8;
using int8 = glm::int8;

using uint16 = glm::uint16;
using int16 = glm::int16;

using uint32 = glm::uint32;
using int32 = glm::int32;

using uint64 = glm::uint64;
using int64 = glm::int64;

template <size_t L, typename T> using vec = glm::vec<L, T>;

using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;

using ivec2 = glm::ivec2;
using ivec3 = glm::ivec3;
using ivec4 = glm::ivec4;

using uvec2 = glm::uvec2;
using uvec3 = glm::uvec3;
using uvec4 = glm::uvec4;

using mat2 = glm::mat2;
using mat3 = glm::mat3;
using mat4 = glm::mat4;
using quat = glm::quat;