cmake_minimum_required(VERSION 3.14)
project(HelloTriangle)

include_directories("${PROJECT_SOURCE_DIR}/src/")
file(GLOB SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.c")

#Cxxdroid-binary: triangle.bin
add_executable(triangle.bin ${SRC_FILES})
find_package(SDL2 REQUIRED)
target_link_libraries(triangle.bin ${SDL2_LIBRARIES})