add_library(Display STATIC
    Display.cpp
    Display.h)
add_subdirectory(Easy2D)
target_link_libraries(Display PRIVATE Easy2D)
# 设置头文件目录，让其他目标能找到 Helloc.h
target_include_directories(Display PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})