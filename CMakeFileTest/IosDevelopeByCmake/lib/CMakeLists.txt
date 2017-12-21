include_directories(${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE Src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )
add_library(add STATIC ${Src})
#SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -arch armv7")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch armv7")

