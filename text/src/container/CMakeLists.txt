add_library(container STATIC
    container.cpp
    container.h)
target_include_directories(container PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})