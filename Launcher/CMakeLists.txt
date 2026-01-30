# --- Collect source files for the executable ---
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# --- Build executable ---
add_executable(Launcher ${SOURCES})
add_dependencies(Launcher Engine)


# --- Include directories ---
target_include_directories(Launcher
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"


)
# --- Link libraries ---
target_link_libraries(Launcher
    PRIVATE
        ${API_NAME}


)
target_compile_definitions(Launcher PRIVATE)
add_executable(Landmark::Launcher ALIAS Launcher)