#ifndef HERO_HPP
#define HERO_HPP

#include "game/Card.hpp"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Hero {
public:
    Hero(const std::string& name) : name(name), health(20), superBlockMeter(0), superBlockUses(3) {}

    void takeDamage(int damage) {
        if (superBlockUses > 0) {
            int block = std::min(damage, 8 - superBlockMeter);
            superBlockMeter += block;
            damage -= block;

            if (superBlockMeter == 8) {
                superBlockMeter = 0;
                superBlockUses--;
                // Grant a superpower
                std::cout << name << " blocks the attack and gains a superpower!" << std::endl;
            }
        }
        health -= damage;
        std::cout << name << " takes " << damage << " damage, health now " << health << std::endl;
    }

    std::string name;
    int health;
    int superBlockMeter;
    int superBlockUses;
    std::vector<std::unique_ptr<Card>> superpowers;
};

#endif // HERO_HPP
