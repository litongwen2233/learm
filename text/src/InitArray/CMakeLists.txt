add_library(InitArray STATIC
InitArray.cpp
InitArray.h
)
target_include_directories(InitArray PUBLIC ${CMAKE_CURRENT_BINARY_DIR})