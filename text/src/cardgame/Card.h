#ifndef __CARD_H__
#define __CARD_H__

#include <iostream>
#include <string>

enum class Suite {
    SPADE = 0,
    HEART = 1,
    CLUB = 2,
    DIAMOND = 3
};

class Card
{
public:
    Suite suite;
    int face;  // 1-13

    Card(Suite suite, int face);
    
    bool operator<(const Card& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
};
class Poker
{
public:
    Poker();
    ~Poker();
private:
    Card cards[52];
};
#endif //__CARD_H__