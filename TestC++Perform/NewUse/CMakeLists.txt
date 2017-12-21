project(test)
cmake_minimum_required(VERSION 2.6)

include_directories(.)
link_directories()
add_definitions("-Wall -g -std=c++11")

aux_source_directory(. DIR_SRC)
add_executable(test ${DIR_SRC})