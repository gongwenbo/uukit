# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib/build

# Include any dependencies generated for this target.
include CMakeFiles/add.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/add.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/add.dir/flags.make

CMakeFiles/add.dir/add.o: CMakeFiles/add.dir/flags.make
CMakeFiles/add.dir/add.o: ../add.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/add.dir/add.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/add.dir/add.o -c /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib/add.cpp

CMakeFiles/add.dir/add.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/add.dir/add.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib/add.cpp > CMakeFiles/add.dir/add.i

CMakeFiles/add.dir/add.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/add.dir/add.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib/add.cpp -o CMakeFiles/add.dir/add.s

CMakeFiles/add.dir/add.o.requires:
.PHONY : CMakeFiles/add.dir/add.o.requires

CMakeFiles/add.dir/add.o.provides: CMakeFiles/add.dir/add.o.requires
	$(MAKE) -f CMakeFiles/add.dir/build.make CMakeFiles/add.dir/add.o.provides.build
.PHONY : CMakeFiles/add.dir/add.o.provides

CMakeFiles/add.dir/add.o.provides.build: CMakeFiles/add.dir/add.o

CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.o: CMakeFiles/add.dir/flags.make
CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.o: CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.o -c /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib/build/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.cpp

CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib/build/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.cpp > CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.i

CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib/build/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.cpp -o CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.s

CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.o.requires:
.PHONY : CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.o.requires

CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.o.provides: CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.o.requires
	$(MAKE) -f CMakeFiles/add.dir/build.make CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.o.provides.build
.PHONY : CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.o.provides

CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.o.provides.build: CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.o

# Object files for target add
add_OBJECTS = \
"CMakeFiles/add.dir/add.o" \
"CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.o"

# External object files for target add
add_EXTERNAL_OBJECTS =

libadd.a: CMakeFiles/add.dir/add.o
libadd.a: CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.o
libadd.a: CMakeFiles/add.dir/build.make
libadd.a: CMakeFiles/add.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libadd.a"
	$(CMAKE_COMMAND) -P CMakeFiles/add.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/add.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/add.dir/build: libadd.a
.PHONY : CMakeFiles/add.dir/build

CMakeFiles/add.dir/requires: CMakeFiles/add.dir/add.o.requires
CMakeFiles/add.dir/requires: CMakeFiles/add.dir/CMakeFiles/2.8.12.2/CompilerIdCXX/CMakeCXXCompilerId.o.requires
.PHONY : CMakeFiles/add.dir/requires

CMakeFiles/add.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/add.dir/cmake_clean.cmake
.PHONY : CMakeFiles/add.dir/clean

CMakeFiles/add.dir/depend:
	cd /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib/build /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib/build /root/uukit/CMakeFileTest/IosDevelopeByCmake/lib/build/CMakeFiles/add.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/add.dir/depend

