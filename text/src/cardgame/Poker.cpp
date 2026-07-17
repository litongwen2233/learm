#include "Poker.h"
#include <random>
#include <algorithm>
#include <iostream>

Poker::Poker() : current(0) {
    for (int s = 0; s < 4; ++s) {
        for (int face = 1; face <= 13; ++face) {
            cards.emplace_back(static_cast<Suite>(s), face);
        }
    }
}

void Poker::shuffle() {
    current = 0;
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

Card Poker::deal() {
    Card card = cards[current];
    ++current;
    return card;
}

bool Poker::has_next() const {
    return current < static_cast<int>(cards.size());
}

void Poker::print_cards() const {
    for (const auto& card : cards) {
        std::cout << card << " ";
    }
    std::cout << std::endl;
}