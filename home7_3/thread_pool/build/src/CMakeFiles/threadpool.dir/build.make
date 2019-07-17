# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/uukit/home7_3/thread_pool

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/uukit/home7_3/thread_pool/build

# Include any dependencies generated for this target.
include src/CMakeFiles/threadpool.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/threadpool.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/threadpool.dir/flags.make

src/CMakeFiles/threadpool.dir/threadpool.cpp.o: src/CMakeFiles/threadpool.dir/flags.make
src/CMakeFiles/threadpool.dir/threadpool.cpp.o: ../src/threadpool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/uukit/home7_3/thread_pool/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/threadpool.dir/threadpool.cpp.o"
	cd /root/uukit/home7_3/thread_pool/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/threadpool.dir/threadpool.cpp.o -c /root/uukit/home7_3/thread_pool/src/threadpool.cpp

src/CMakeFiles/threadpool.dir/threadpool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threadpool.dir/threadpool.cpp.i"
	cd /root/uukit/home7_3/thread_pool/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/uukit/home7_3/thread_pool/src/threadpool.cpp > CMakeFiles/threadpool.dir/threadpool.cpp.i

src/CMakeFiles/threadpool.dir/threadpool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threadpool.dir/threadpool.cpp.s"
	cd /root/uukit/home7_3/thread_pool/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/uukit/home7_3/thread_pool/src/threadpool.cpp -o CMakeFiles/threadpool.dir/threadpool.cpp.s

src/CMakeFiles/threadpool.dir/threadpool.cpp.o.requires:

.PHONY : src/CMakeFiles/threadpool.dir/threadpool.cpp.o.requires

src/CMakeFiles/threadpool.dir/threadpool.cpp.o.provides: src/CMakeFiles/threadpool.dir/threadpool.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/threadpool.dir/build.make src/CMakeFiles/threadpool.dir/threadpool.cpp.o.provides.build
.PHONY : src/CMakeFiles/threadpool.dir/threadpool.cpp.o.provides

src/CMakeFiles/threadpool.dir/threadpool.cpp.o.provides.build: src/CMakeFiles/threadpool.dir/threadpool.cpp.o


# Object files for target threadpool
threadpool_OBJECTS = \
"CMakeFiles/threadpool.dir/threadpool.cpp.o"

# External object files for target threadpool
threadpool_EXTERNAL_OBJECTS =

src/libthreadpool.a: src/CMakeFiles/threadpool.dir/threadpool.cpp.o
src/libthreadpool.a: src/CMakeFiles/threadpool.dir/build.make
src/libthreadpool.a: src/CMakeFiles/threadpool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/uukit/home7_3/thread_pool/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libthreadpool.a"
	cd /root/uukit/home7_3/thread_pool/build/src && $(CMAKE_COMMAND) -P CMakeFiles/threadpool.dir/cmake_clean_target.cmake
	cd /root/uukit/home7_3/thread_pool/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threadpool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/threadpool.dir/build: src/libthreadpool.a

.PHONY : src/CMakeFiles/threadpool.dir/build

src/CMakeFiles/threadpool.dir/requires: src/CMakeFiles/threadpool.dir/threadpool.cpp.o.requires

.PHONY : src/CMakeFiles/threadpool.dir/requires

src/CMakeFiles/threadpool.dir/clean:
	cd /root/uukit/home7_3/thread_pool/build/src && $(CMAKE_COMMAND) -P CMakeFiles/threadpool.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/threadpool.dir/clean

src/CMakeFiles/threadpool.dir/depend:
	cd /root/uukit/home7_3/thread_pool/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/uukit/home7_3/thread_pool /root/uukit/home7_3/thread_pool/src /root/uukit/home7_3/thread_pool/build /root/uukit/home7_3/thread_pool/build/src /root/uukit/home7_3/thread_pool/build/src/CMakeFiles/threadpool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/threadpool.dir/depend
