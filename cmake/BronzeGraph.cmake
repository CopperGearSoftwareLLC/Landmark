include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)      
# --- Fetch BronzeGraph from your repo ---
FetchContent_Declare(
    bronzegraph
    GIT_REPOSITORY https://github.com/CopperGearSoftwareLLC/BronzeGraph.git  # Replace with actual URL
    GIT_TAG main  # Or a specific tag/branch
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(bronzegraph)