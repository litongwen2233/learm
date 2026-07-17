add_library(helloc STATIC
    Helloc.cpp
    Helloc.h)
# 设置头文件目录，让其他目标能找到 Helloc.h
target_include_directories(helloc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})