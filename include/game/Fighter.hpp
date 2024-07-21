#ifndef FIGHTER_HPP
#define FIGHTER_HPP

#include "game/Card.hpp"
#include "game/Observer.hpp"
#include "game/DamagePackage.hpp"
#include <set>

class Fighter : public Card {
public:
    int strength;
    int health;
    bool deathtouch = false;
    bool markedForDeath = false;

    void takeDamage(int damage) {
        health -= damage;
        notify(DamageEvent("", name, damage));
        if (health <= 0) {
            notify(DeathEvent(name));
        }
    }

    virtual void attack(Fighter* opponent, DamagePackage damagePackage) {
        if (opponent) {
            int damage = damagePackage.getDamage();
            notify(DamageEvent(name, opponent->name, damage));
            opponent->takeDamage(damage);
            if (deathtouch && strength > 0) {
                opponent->markedForDeath = true;
                notify(DeathEvent(opponent->name));
            }
        }
    }

    void play() const override {
        std::cout << name << " played with " << strength << " strength and " << health << " health." << std::endl;
    }

    virtual void onPlantDeath(const DeathEvent& event) {}
};

class Plant : public Fighter {
public:
    void play() const override {
        std::cout << "Plant " << name << " played with " << strength << " strength and " << health << " health." << std::endl;
    }
};

class Zombie : public Fighter {
public:
    void play() const override {
        std::cout << "Zombie " << name << " played with " << strength << " strength and " << health << " health." << std::endl;
    }
};

class Trick : public Card {
public:
    virtual void apply() = 0;
};

class SpecialZombie : public Zombie, public Observer {
public:
    void onNotify(const Event& event) override {
        if (event.getType() == "DeathEvent") {
            const DeathEvent& deathEvent = static_cast<const DeathEvent&>(event);
            onPlantDeath(deathEvent);
        }
    }

    void onPlantDeath(const DeathEvent& event) override {
        strength += 1;
        health += 1;
        std::cout << name << " gains +1 strength and +1 health due to the death of " << event.name << std::endl;
    }
};

#endif // FIGHTER_HPP