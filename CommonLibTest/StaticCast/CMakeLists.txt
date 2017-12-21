project(test)
set(CMAKE_CXX_FLAGS "-m32")
add_definitions("-Wall -g")

#include_directories(./inc)
#link_directories(./lib)
#link_libraries(..)

aux_source_directory(. DIR_SORCE)

add_executable(test ${DIR_SORCE})
#target_link_libraries(test ...)


