# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Users\ASUS\Desktop\CLion 2019.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Users\ASUS\Desktop\CLion 2019.2.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Matam\HW3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Matam\HW3\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HW3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HW3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HW3.dir/flags.make

CMakeFiles/HW3.dir/main2.cpp.obj: CMakeFiles/HW3.dir/flags.make
CMakeFiles/HW3.dir/main2.cpp.obj: ../main2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Matam\HW3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HW3.dir/main2.cpp.obj"
	C:\Users\ASUS\Desktop\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\HW3.dir\main2.cpp.obj -c C:\Matam\HW3\main2.cpp

CMakeFiles/HW3.dir/main2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW3.dir/main2.cpp.i"
	C:\Users\ASUS\Desktop\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Matam\HW3\main2.cpp > CMakeFiles\HW3.dir\main2.cpp.i

CMakeFiles/HW3.dir/main2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW3.dir/main2.cpp.s"
	C:\Users\ASUS\Desktop\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Matam\HW3\main2.cpp -o CMakeFiles\HW3.dir\main2.cpp.s

# Object files for target HW3
HW3_OBJECTS = \
"CMakeFiles/HW3.dir/main2.cpp.obj"

# External object files for target HW3
HW3_EXTERNAL_OBJECTS =

HW3.exe: CMakeFiles/HW3.dir/main2.cpp.obj
HW3.exe: CMakeFiles/HW3.dir/build.make
HW3.exe: CMakeFiles/HW3.dir/linklibs.rsp
HW3.exe: CMakeFiles/HW3.dir/objects1.rsp
HW3.exe: CMakeFiles/HW3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Matam\HW3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HW3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\HW3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HW3.dir/build: HW3.exe

.PHONY : CMakeFiles/HW3.dir/build

CMakeFiles/HW3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\HW3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/HW3.dir/clean

CMakeFiles/HW3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Matam\HW3 C:\Matam\HW3 C:\Matam\HW3\cmake-build-debug C:\Matam\HW3\cmake-build-debug C:\Matam\HW3\cmake-build-debug\CMakeFiles\HW3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HW3.dir/depend

