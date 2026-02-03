# --- Collect source files for the executable ---
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# --- Build executable ---
add_library(LandmarkEngine STATIC ${SOURCES})



# --- Include directories ---
target_include_directories(LandmarkEngine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        ${EGL_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
         ${glad_SOURCE_DIR}/include
        # ${imgui_SOURCE_DIR}
        # ${implot_SOURCE_DIR}
        #${glfw_SOURCE_DIR}/include
        #${glew_SOURCE_DIR}/include
        #${IMNODEFLOW_DIR}/include
        #${imnodeflow_SOURCE_DIR}/include

)
# --- Link libraries ---
target_link_libraries(LandmarkEngine
    PRIVATE
        ${API_NAME}
        imgui_lib
        implot_lib
        Boost::stacktrace_addr2line
        fg::FrameGraph
        OpenGL::GL
        BrassUtils
        ${EGL_LIBRARIES}
        #glad
        

)
target_compile_definitions(LandmarkEngine PRIVATE)
add_library(Landmark::Engine ALIAS LandmarkEngine)