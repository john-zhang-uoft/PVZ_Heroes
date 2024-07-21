#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "game/Fighter.hpp"
#include "game/DamagePackage.hpp"

class Environment : public Card {
public:
    virtual void applyEffect(Fighter* fighter) = 0;
    virtual void removeEffect(Fighter* fighter) = 0;

    virtual void modifyDamage(DamagePackage& damagePackage, Fighter* attacker) = 0;
};

class DoubleDamageEnvironment : public Environment {
public:
    void play() const override {
        std::cout << "Environment" << name << " played." << std::endl;
    }

    void applyEffect(Fighter* fighter) override {
        std::cout << "Double Damage Environment applied to " << fighter->name << std::endl;
    }

    void removeEffect(Fighter* fighter) override {
        std::cout << "Double Damage Environment removed from " << fighter->name << std::endl;
    }

    void modifyDamage(DamagePackage& damagePackage, Fighter* attacker) override {
        auto zombie = dynamic_cast<Zombie*>(attacker);
        if (zombie) {
            damagePackage.doubleDamage = true;
        }
    }
};

#endif // ENVIRONMENT_HPP