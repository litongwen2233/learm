#规定CMake的最低版本
cmake_minimum_required(VERSION 3.14)
#工程名称和语言
Project(text LANGUAGES CXX)
# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#添加子目录
add_subdirectory(src)