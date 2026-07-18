# cmake_minimum_required(VERSION 3.15)
project(Easy2D VERSION 1.0.0 LANGUAGES CXX)
# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# 设置输出目录（可选）
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src/Easy2D)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src/Easy2D)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src/Easy2D)
# 设置包含目录
include_directories(${PROJECT_SOURCE_DIR}/include)
# 收集源文件
file(GLOB_RECURSE SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*/*.cpp"
)
# 创建库
add_library(Easy2D STATIC ${SRC_FILES})
# 设置目标属性
target_include_directories(Easy2D PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)