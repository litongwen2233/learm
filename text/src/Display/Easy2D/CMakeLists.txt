# 收集源文件
file(GLOB_RECURSE SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.cpp"
)
# 创建库
add_library(Easy2D STATIC ${SRC_FILES})
# 设置头文件目录
target_include_directories(Easy2D PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)