PROJECT(test_hwsdkc)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE_DIRECTORIES(/root/uukit/DoorBell/inc)
LINK_DIRECTORIES(/root/uukit/DoorBell/lib)
add_definitions(-Wall -g)
#LINK_LIBRARIES(hwsdkc cu)
SET ( CMAKE_CXX_FLAGS "-m32" )
#ADD_SUBDIRECTORY(src)
#list (REMOVE_ITEM DIR_SRCS main.cpp CMakeLists.txt)
# SET( ALL_SOURCES 
#        ${SRC_LIDAR_FORMAT} 
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
ADD_EXECUTABLE(test_hwsdkc ${DIR_SRCS})

TARGET_LINK_LIBRARIES(test_hwsdkc -lhwsdkc -lcu)


