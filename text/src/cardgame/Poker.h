#ifndef POKER_H
#define POKER_H

#include <vector>
#include "Card.h"

class Poker {
private:
    std::vector<Card> cards;
    int current;  // 发牌位置

public:
    Poker();
    void shuffle();
    Card deal();
    bool has_next() const;
    void print_cards() const;  // 仅用于测试
};

#endif // POKER_H