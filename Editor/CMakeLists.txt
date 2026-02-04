

# --- Collect source files ---
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(LandmarkEditor ${SOURCES})
add_dependencies(LandmarkEditor LandmarkEngine)


# --- Include directories ---
target_include_directories(LandmarkEditor
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        #${portaudio_SOURCE_DIR}/include
        ${LLVM_INCLUDE_DIRS}
)

# --- Link libraries ---
target_link_libraries(LandmarkEditor
    PUBLIC
        Landmark::Engine
        Landmark::Deps
        Qt6::Widgets
        Qt6::OpenGL

)
target_compile_definitions(LandmarkEditor
    PRIVATE
        ${LLVM_DEFINITIONS}
)
# --- Optional compile flags from pkg-config ---
target_compile_options(LandmarkEditor PRIVATE ${PORTAUDIO_CFLAGS_OTHER} ${LLVM_CXXFLAGS})

add_executable(Landmark::Editor ALIAS LandmarkEditor)