cmake_minimum_required(VERSION 3.10)

project(Chess LANGUAGES CXX)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Tell compiler where headers are
include_directories(include)

# Collect source files
file(GLOB SOURCE_FILES src/*.cpp)

# Create the executable
add_executable(app ${SOURCE_FILES})

target_link_libraries(app
    SDL2::SDL2
    SDL2_image::SDL2_image
)


