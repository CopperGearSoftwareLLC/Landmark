#pragma once

#include "LandmarkEngine.hpp"

// type alias for callback
using SystemRegisterFunc = void(*)();

// get the global registration list (function-local static -> safe init order)
inline std::vector<std::pair<std::string_view, SystemRegisterFunc>>& GetSystemRegistrationList() {
    static std::vector<std::pair<std::string_view, SystemRegisterFunc>> list;
    return list;
}

// macro: put this one line where you define the system (header or cpp).
// It creates a small helper whose ctor pushes { "TypeName", callback } to the list.
#define LANDMARK_REGISTER_SYSTEM(TYPE)                                                      \
namespace {                                                                                \
    inline void LANDMARK_register_func_##TYPE() {                                          \
        LandmarkEngine::Get().AddSystem<TYPE>();                                          \
    }                                                                                      \
    struct LANDMARK_register_helper_##TYPE {                                               \
        LANDMARK_register_helper_##TYPE() noexcept {                                       \
            GetSystemRegistrationList().emplace_back(#TYPE, &LANDMARK_register_func_##TYPE); \
        }                                                                                  \
    };                                                                                     \
    /* create one helper object per TU that includes the header; duplicates will be deduped at engine start */ \
    inline LANDMARK_register_helper_##TYPE LANDMARK_register_instance_##TYPE;              \
}