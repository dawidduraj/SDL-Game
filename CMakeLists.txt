cmake_minimum_required(VERSION 3.10)
project(sdl-game)

# Find the SDL2 package 
find_package(SDL2 REQUIRED)

# GLAD
include_directories(${CMAKE_SOURCE_DIR}/lib/glad/include)
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)

# Collect all .c files in the src directory
file(GLOB SOURCES "src/*.c")

# Add your executable
add_executable(sdl-game ${SOURCES})

# Link SDL2 to your executable
target_link_libraries(sdl-game PRIVATE SDL2::SDL2main SDL2::SDL2 glad)
