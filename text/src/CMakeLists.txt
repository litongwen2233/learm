#生成可执行文件
add_executable(mytext main.cpp)
#添加子目录
add_subdirectory(helloc)
add_subdirectory(InitArray)
add_subdirectory(cardgame)
#链接子目录生成的库
target_link_libraries(mytext PRIVATE helloc)
target_link_libraries(mytext PRIVATE InitArray)
target_link_libraries(mytext PRIVATE cardgame)