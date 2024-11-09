cmake_minimum_required(VERSION 3.26)
project(audio_visualizer_c)

# Include Directories
include_directories(header_files)
include_directories(resources)
include_directories(raylib)

# Add Raylib static library
add_library(RAYLIB STATIC IMPORTED)
set_target_properties(RAYLIB PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/raylib/libraylib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/raylib"
)

# Add the executable
add_executable(audio_visualizer_c src/main.c)

# Link the Raylib library to the executable
target_link_libraries(audio_visualizer_c PRIVATE RAYLIB)

# Link system libraries (OpenGL, GDI, and WinMM)
target_link_libraries(audio_visualizer_c PRIVATE 
    opengl32
    gdi32
    winmm
)