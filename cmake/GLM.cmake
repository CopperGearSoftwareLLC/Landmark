include(FetchContent)

message(STATUS "Fetching GLM")
SET(GLM_BUILD_TESTS OFF)
SET(GLM_ENABLE_CXX_20 ON)
SET(GLM_ENABLE_LANG_EXTENSIONS ON)

FetchContent_Declare(
  glm
  URL https://github.com/g-truc/glm/archive/refs/tags/1.0.3.tar.gz
  USES_TERMINAL_DOWNLOAD TRUE
  DOWNLOAD_NO_EXTRACT FALSE
)
FetchContent_MakeAvailable(glm)
