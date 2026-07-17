#include "Card.h"

// 全局变量定义
const std::string suite_symbols = "♠♥♣♦";
const std::string face_names[] = {
    "", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
};

Card::Card(Suite suite, int face) : suite(suite), face(face) {}

bool Card::operator<(const Card& other) const {
    if (suite == other.suite) {
        return face < other.face;
    }
    return static_cast<int>(suite) < static_cast<int>(other.suite);
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << suite_symbols[static_cast<int>(card.suite)] << face_names[card.face];
    return os;
}