# --- Collect source files for the executable ---
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# --- Build executable ---
add_executable(Engine ${SOURCES})
add_dependencies(Engine Module)


# --- Include directories ---
target_include_directories(Engine
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        # ${imgui_SOURCE_DIR}
        # ${implot_SOURCE_DIR}
        #${glfw_SOURCE_DIR}/include
        #${glew_SOURCE_DIR}/include
        #${IMNODEFLOW_DIR}/include
        #${imnodeflow_SOURCE_DIR}/include

)
# --- Link libraries ---
target_link_libraries(Engine
    PRIVATE
        ${API_NAME}
        #glfw
        #glew_s
        #imgui_lib
        #implot_lib
        Boost::stacktrace_addr2line
        #OpenGL::GL

)
target_compile_definitions(Engine PRIVATE)
add_executable(Landmark::Engine ALIAS Engine)