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
CMAKE_SOURCE_DIR = /home/mayank/Downloads/nirmal_git_repo/wifi/example-api-client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mayank/Downloads/nirmal_git_repo/wifi/example-api-client/build

# Include any dependencies generated for this target.
include CMakeFiles/example-api-client-exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/example-api-client-exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/example-api-client-exe.dir/flags.make

CMakeFiles/example-api-client-exe.dir/src/App.cpp.o: CMakeFiles/example-api-client-exe.dir/flags.make
CMakeFiles/example-api-client-exe.dir/src/App.cpp.o: ../src/App.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mayank/Downloads/nirmal_git_repo/wifi/example-api-client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/example-api-client-exe.dir/src/App.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example-api-client-exe.dir/src/App.cpp.o -c /home/mayank/Downloads/nirmal_git_repo/wifi/example-api-client/src/App.cpp

CMakeFiles/example-api-client-exe.dir/src/App.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example-api-client-exe.dir/src/App.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mayank/Downloads/nirmal_git_repo/wifi/example-api-client/src/App.cpp > CMakeFiles/example-api-client-exe.dir/src/App.cpp.i

CMakeFiles/example-api-client-exe.dir/src/App.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example-api-client-exe.dir/src/App.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mayank/Downloads/nirmal_git_repo/wifi/example-api-client/src/App.cpp -o CMakeFiles/example-api-client-exe.dir/src/App.cpp.s

# Object files for target example-api-client-exe
example__api__client__exe_OBJECTS = \
"CMakeFiles/example-api-client-exe.dir/src/App.cpp.o"

# External object files for target example-api-client-exe
example__api__client__exe_EXTERNAL_OBJECTS =

example-api-client-exe: CMakeFiles/example-api-client-exe.dir/src/App.cpp.o
example-api-client-exe: CMakeFiles/example-api-client-exe.dir/build.make
example-api-client-exe: libexample-api-client-lib.a
example-api-client-exe: /usr/local/lib/oatpp-1.3.0/liboatpp-curl.a
example-api-client-exe: /usr/local/lib/oatpp-1.3.0/liboatpp-openssl.a
example-api-client-exe: /usr/local/lib/oatpp-1.3.0/liboatpp-test.a
example-api-client-exe: /usr/local/lib/oatpp-1.3.0/liboatpp.a
example-api-client-exe: /usr/local/lib/libssl.a
example-api-client-exe: /usr/lib/x86_64-linux-gnu/libcrypto.so
example-api-client-exe: CMakeFiles/example-api-client-exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mayank/Downloads/nirmal_git_repo/wifi/example-api-client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable example-api-client-exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example-api-client-exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/example-api-client-exe.dir/build: example-api-client-exe

.PHONY : CMakeFiles/example-api-client-exe.dir/build

CMakeFiles/example-api-client-exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/example-api-client-exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/example-api-client-exe.dir/clean

CMakeFiles/example-api-client-exe.dir/depend:
	cd /home/mayank/Downloads/nirmal_git_repo/wifi/example-api-client/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mayank/Downloads/nirmal_git_repo/wifi/example-api-client /home/mayank/Downloads/nirmal_git_repo/wifi/example-api-client /home/mayank/Downloads/nirmal_git_repo/wifi/example-api-client/build /home/mayank/Downloads/nirmal_git_repo/wifi/example-api-client/build /home/mayank/Downloads/nirmal_git_repo/wifi/example-api-client/build/CMakeFiles/example-api-client-exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/example-api-client-exe.dir/depend

