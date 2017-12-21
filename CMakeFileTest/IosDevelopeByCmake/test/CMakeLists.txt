cmake_minimum_required(VERSION 2.8)
project(test)
add_definitions(-Wall -g -std=c++11)
include_directories(../lib)
link_directories(../lib/build)

aux_source_directory(./ DIR_SRC)
#add_subdirectory(../) \
Include the directory source_dir in your project.\
This directory must contain a CMakeLists.txt file.
add_executable(out ${DIR_SRC})
target_link_libraries(out libadd.a)


