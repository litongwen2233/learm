add_library(cardgame STATIC
    Card.cpp
    Card.h
    Poker.cpp
    Poker.h
    Player.cpp
    Player.h
    )
# 设置头文件目录，让其他目标能找到 Card.h
target_include_directories(cardgame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})