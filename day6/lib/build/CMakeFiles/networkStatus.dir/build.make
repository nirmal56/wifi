# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/nirmal/user/wifi/day6/lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nirmal/user/wifi/day6/lib/build

# Include any dependencies generated for this target.
include CMakeFiles/networkStatus.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/networkStatus.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/networkStatus.dir/flags.make

CMakeFiles/networkStatus.dir/main.cpp.o: CMakeFiles/networkStatus.dir/flags.make
CMakeFiles/networkStatus.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nirmal/user/wifi/day6/lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/networkStatus.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/networkStatus.dir/main.cpp.o -c /home/nirmal/user/wifi/day6/lib/main.cpp

CMakeFiles/networkStatus.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/networkStatus.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nirmal/user/wifi/day6/lib/main.cpp > CMakeFiles/networkStatus.dir/main.cpp.i

CMakeFiles/networkStatus.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/networkStatus.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nirmal/user/wifi/day6/lib/main.cpp -o CMakeFiles/networkStatus.dir/main.cpp.s

CMakeFiles/networkStatus.dir/checkstatus.cpp.o: CMakeFiles/networkStatus.dir/flags.make
CMakeFiles/networkStatus.dir/checkstatus.cpp.o: ../checkstatus.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nirmal/user/wifi/day6/lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/networkStatus.dir/checkstatus.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/networkStatus.dir/checkstatus.cpp.o -c /home/nirmal/user/wifi/day6/lib/checkstatus.cpp

CMakeFiles/networkStatus.dir/checkstatus.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/networkStatus.dir/checkstatus.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nirmal/user/wifi/day6/lib/checkstatus.cpp > CMakeFiles/networkStatus.dir/checkstatus.cpp.i

CMakeFiles/networkStatus.dir/checkstatus.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/networkStatus.dir/checkstatus.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nirmal/user/wifi/day6/lib/checkstatus.cpp -o CMakeFiles/networkStatus.dir/checkstatus.cpp.s

# Object files for target networkStatus
networkStatus_OBJECTS = \
"CMakeFiles/networkStatus.dir/main.cpp.o" \
"CMakeFiles/networkStatus.dir/checkstatus.cpp.o"

# External object files for target networkStatus
networkStatus_EXTERNAL_OBJECTS =

networkStatus: CMakeFiles/networkStatus.dir/main.cpp.o
networkStatus: CMakeFiles/networkStatus.dir/checkstatus.cpp.o
networkStatus: CMakeFiles/networkStatus.dir/build.make
networkStatus: CMakeFiles/networkStatus.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nirmal/user/wifi/day6/lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable networkStatus"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/networkStatus.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/networkStatus.dir/build: networkStatus

.PHONY : CMakeFiles/networkStatus.dir/build

CMakeFiles/networkStatus.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/networkStatus.dir/cmake_clean.cmake
.PHONY : CMakeFiles/networkStatus.dir/clean

CMakeFiles/networkStatus.dir/depend:
	cd /home/nirmal/user/wifi/day6/lib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nirmal/user/wifi/day6/lib /home/nirmal/user/wifi/day6/lib /home/nirmal/user/wifi/day6/lib/build /home/nirmal/user/wifi/day6/lib/build /home/nirmal/user/wifi/day6/lib/build/CMakeFiles/networkStatus.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/networkStatus.dir/depend

