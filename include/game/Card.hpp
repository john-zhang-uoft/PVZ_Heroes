#ifndef CARD_HPP
#define CARD_HPP

#include "game/Observer.hpp"

#include <string>

class Card : public Subject {
public:
    virtual void play() const = 0;
    virtual ~Card() = default;

    std::string name;
    int cost;
};

#endif // CARD_HPP