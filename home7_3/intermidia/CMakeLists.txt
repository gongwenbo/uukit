cmake_minimum_required(VERSION 2.6)
project("designer")
include_directories(./inc ./src)
add_definitions("-g -Wall -std=c++11")
add_subdirectory(./src)
aux_source_directory(./ SRC)
add_executable(media ${SRC} )
target_link_libraries(media _media)



