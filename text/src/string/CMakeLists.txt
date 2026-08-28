add_library(string STATIC 
    String_text.cpp
    string_text.h)
target_include_directories(string PUBLIC $(CMAKE_CURRENT_SOURCE_DIR))
