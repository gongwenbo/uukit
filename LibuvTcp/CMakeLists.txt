cmake_minimum_required(VERSION 2.6)
project(test_libuv)
add_definitions("-Wall -g -std=c++11")

include_directories(./)
#aux_source_directory(./)
add_executable(ser ./server.cpp)
add_executable(cli ./client.cpp)

target_link_libraries(ser -luv)
target_link_libraries(cli -luv)