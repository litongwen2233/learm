#生成可执行文件
add_executable(mytext main.cpp)
#添加子目录
add_subdirectory(helloc)
add_subdirectory(InitArray)
add_subdirectory(string)
add_subdirectory(aixin)
# add_subdirectory(cardgame)
add_subdirectory(Display)
add_subdirectory(container)
#链接子目录生成的库
target_link_libraries(mytext PRIVATE helloc)
target_link_libraries(mytext PRIVATE InitArray)
target_link_libraries(mytext PRIVATE string)
target_link_libraries(mytext PRIVATE aixin)
# target_link_libraries(mytext PRIVATE cardgame)
target_link_libraries(mytext PRIVATE Display)
target_link_libraries(mytext PRIVATE container)