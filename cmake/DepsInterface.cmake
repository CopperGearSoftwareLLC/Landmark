cmake_minimum_required(VERSION 3.16)

add_library(Deps INTERFACE)

# Link all dependencies to this INTERFACE library
target_link_libraries(Deps INTERFACE         
portaudio
BrassUtils::BrassUtils
Boost::headers
Boost::bimap
Boost::math
Boost::static_string
Boost::graph)

# Include directories (optional)
#target_include_directories(MyDeps::all INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Landmark::Deps ALIAS Deps)