add_library(aixin STATIC
    aixin.cpp
    aixin.h)
# 设置头文件目录，让其他目标能找到 Helloc.h
target_include_directories(aixin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})