# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer\build

# Include any dependencies generated for this target.
include CMakeFiles/audio_visualizer_c.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/audio_visualizer_c.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/audio_visualizer_c.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/audio_visualizer_c.dir/flags.make

CMakeFiles/audio_visualizer_c.dir/src/main.c.obj: CMakeFiles/audio_visualizer_c.dir/flags.make
CMakeFiles/audio_visualizer_c.dir/src/main.c.obj: CMakeFiles/audio_visualizer_c.dir/includes_C.rsp
CMakeFiles/audio_visualizer_c.dir/src/main.c.obj: C:/Users/franc/Documents/Personal_Projects/raylib_audio_visualizer/src/main.c
CMakeFiles/audio_visualizer_c.dir/src/main.c.obj: CMakeFiles/audio_visualizer_c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/audio_visualizer_c.dir/src/main.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/audio_visualizer_c.dir/src/main.c.obj -MF CMakeFiles\audio_visualizer_c.dir\src\main.c.obj.d -o CMakeFiles\audio_visualizer_c.dir\src\main.c.obj -c C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer\src\main.c

CMakeFiles/audio_visualizer_c.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/audio_visualizer_c.dir/src/main.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer\src\main.c > CMakeFiles\audio_visualizer_c.dir\src\main.c.i

CMakeFiles/audio_visualizer_c.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/audio_visualizer_c.dir/src/main.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer\src\main.c -o CMakeFiles\audio_visualizer_c.dir\src\main.c.s

CMakeFiles/audio_visualizer_c.dir/src/tinyfiledialogs.c.obj: CMakeFiles/audio_visualizer_c.dir/flags.make
CMakeFiles/audio_visualizer_c.dir/src/tinyfiledialogs.c.obj: CMakeFiles/audio_visualizer_c.dir/includes_C.rsp
CMakeFiles/audio_visualizer_c.dir/src/tinyfiledialogs.c.obj: C:/Users/franc/Documents/Personal_Projects/raylib_audio_visualizer/src/tinyfiledialogs.c
CMakeFiles/audio_visualizer_c.dir/src/tinyfiledialogs.c.obj: CMakeFiles/audio_visualizer_c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/audio_visualizer_c.dir/src/tinyfiledialogs.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/audio_visualizer_c.dir/src/tinyfiledialogs.c.obj -MF CMakeFiles\audio_visualizer_c.dir\src\tinyfiledialogs.c.obj.d -o CMakeFiles\audio_visualizer_c.dir\src\tinyfiledialogs.c.obj -c C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer\src\tinyfiledialogs.c

CMakeFiles/audio_visualizer_c.dir/src/tinyfiledialogs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/audio_visualizer_c.dir/src/tinyfiledialogs.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer\src\tinyfiledialogs.c > CMakeFiles\audio_visualizer_c.dir\src\tinyfiledialogs.c.i

CMakeFiles/audio_visualizer_c.dir/src/tinyfiledialogs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/audio_visualizer_c.dir/src/tinyfiledialogs.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer\src\tinyfiledialogs.c -o CMakeFiles\audio_visualizer_c.dir\src\tinyfiledialogs.c.s

# Object files for target audio_visualizer_c
audio_visualizer_c_OBJECTS = \
"CMakeFiles/audio_visualizer_c.dir/src/main.c.obj" \
"CMakeFiles/audio_visualizer_c.dir/src/tinyfiledialogs.c.obj"

# External object files for target audio_visualizer_c
audio_visualizer_c_EXTERNAL_OBJECTS =

audio_visualizer_c.exe: CMakeFiles/audio_visualizer_c.dir/src/main.c.obj
audio_visualizer_c.exe: CMakeFiles/audio_visualizer_c.dir/src/tinyfiledialogs.c.obj
audio_visualizer_c.exe: CMakeFiles/audio_visualizer_c.dir/build.make
audio_visualizer_c.exe: C:/Users/franc/Documents/Personal_Projects/raylib_audio_visualizer/raylib/libraylib.a
audio_visualizer_c.exe: CMakeFiles/audio_visualizer_c.dir/linkLibs.rsp
audio_visualizer_c.exe: CMakeFiles/audio_visualizer_c.dir/objects1.rsp
audio_visualizer_c.exe: CMakeFiles/audio_visualizer_c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable audio_visualizer_c.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\audio_visualizer_c.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/audio_visualizer_c.dir/build: audio_visualizer_c.exe
.PHONY : CMakeFiles/audio_visualizer_c.dir/build

CMakeFiles/audio_visualizer_c.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\audio_visualizer_c.dir\cmake_clean.cmake
.PHONY : CMakeFiles/audio_visualizer_c.dir/clean

CMakeFiles/audio_visualizer_c.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer\build C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer\build C:\Users\franc\Documents\Personal_Projects\raylib_audio_visualizer\build\CMakeFiles\audio_visualizer_c.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/audio_visualizer_c.dir/depend

