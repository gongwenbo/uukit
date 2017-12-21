project(test)
include_directories(./)
link_directories(./)
add_definitions("-Wall -g -std=c++11")
link_libraries(-lboost_system)
aux_source_directory(. DIR_SORCE)
add_executable(test ${DIR_SORCE})

#target_link_libraries(test ...)