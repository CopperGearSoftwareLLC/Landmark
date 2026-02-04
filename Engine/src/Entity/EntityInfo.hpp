#pragma once

#include "Math.hpp"
#include "boost/static_string.hpp"
struct EntityInfo
{
    const static inline uint32 ENTITY_NAME_LENGTH_MAX = 64;
    boost::static_string<ENTITY_NAME_LENGTH_MAX> Name;
};