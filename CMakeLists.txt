cmake_minimum_required(VERSION 3.20)

project(TaikoCV LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_compile_options (-Wall -Wextra -Wpedantic)

find_package (OpenCV REQUIRED)
include_directories (${OpenCV_INCLUDE_DIRS})

include_directories (${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)