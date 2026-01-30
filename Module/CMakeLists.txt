

# --- Collect source files ---
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(Module STATIC ${SOURCES})
target_compile_definitions(Module PUBLIC RAINFALLAPI_STATIC)



# --- Include directories ---
target_include_directories(Module
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        ${portaudio_SOURCE_DIR}/include
        ${LLVM_INCLUDE_DIRS}
)

# --- Link libraries ---
target_link_libraries(Module
    PUBLIC
        Landmark::Deps
)
target_compile_definitions(Module
    PRIVATE
        ${LLVM_DEFINITIONS}
)
# --- Optional compile flags from pkg-config ---
target_compile_options(Module PRIVATE ${PORTAUDIO_CFLAGS_OTHER} ${LLVM_CXXFLAGS})

add_library(Landmark::Module ALIAS Module)