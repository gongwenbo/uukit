project(test)
set(CMAKE_CXX_FLAGS "-std=c++11")
add_definitions("-Wall -g")
# 都可以设置编译选项。
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_directories(/usr/local/lib)
#link_libraries(..)

aux_source_directory(. DIR_SORCE)

add_executable(test ${DIR_SORCE})
target_link_libraries(test -lboost_system -lboost_thread)


