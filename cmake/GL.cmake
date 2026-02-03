cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0072 NEW) # Prefer GLVND

# --- OpenGL ---
find_package(OpenGL REQUIRED)
if(NOT OpenGL_FOUND)
    message(FATAL_ERROR "OpenGL not found")
endif()

# --- EGL ---
find_package(PkgConfig REQUIRED)
pkg_check_modules(EGL REQUIRED egl)

# --- GLAD ---
include(FetchContent)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8 # or latest stable
    SOURCE_SUBDIR  cmake
)

FetchContent_MakeAvailable(glad)
glad_add_library(glad_gl_core_43 STATIC REPRODUCIBLE LOADER API gl:core=4.3)