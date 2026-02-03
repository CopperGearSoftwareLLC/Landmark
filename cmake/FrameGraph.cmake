include(FetchContent)

FetchContent_Declare(
  FrameGraph
  GIT_REPOSITORY https://github.com/skaarj1989/FrameGraph.git
  GIT_TAG master)
  set(FG_BUILD_TEST OFF)
FetchContent_MakeAvailable(FrameGraph)
