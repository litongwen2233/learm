#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Card.h"

class Player {
public:
    std::string name;
    std::vector<Card> cards;

    Player(const std::string& name);
    void get_one(const Card& card);
    void arrange();
};

#endif // PLAYER_H