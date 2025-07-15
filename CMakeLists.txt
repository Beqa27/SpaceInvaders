cmake_minimum_required(VERSION 3.10)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 17)

# Find SDL2 and SDL2_image using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

# Your main file(s)
add_executable(SpaceInvaders src/main.cpp
    src/Player.cpp
    src/bullet.cpp
)

# Include directories
target_include_directories(SpaceInvaders PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(SpaceInvaders
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
