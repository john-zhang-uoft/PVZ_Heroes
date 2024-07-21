#ifndef BATTLEFIELD_HPP
#define BATTLEFIELD_HPP

#include "game/Card.hpp"
#include "game/Hero.hpp"
#include "game/Fighter.hpp"
#include "game/Environment.hpp"
#include <vector>
#include <memory>

class BattleField : public Subject {
public:
    struct Slot {
        std::unique_ptr<Fighter> plant;
        std::unique_ptr<Fighter> zombie;
        std::unique_ptr<Environment> environment;
    };

    void addPlant(int column, std::unique_ptr<Fighter> plant) {
        slots[column].plant = std::move(plant);
    }

    void addZombie(int column, std::unique_ptr<Fighter> zombie) {
        slots[column].zombie = std::move(zombie);
    }

    void addEnvironment(int column, std::unique_ptr<Environment> environment) {
        if (slots[column].environment) {
            slots[column].environment->removeEffect(slots[column].zombie.get());
        }
        slots[column].environment = std::move(environment);
        if (slots[column].zombie) {
            slots[column].environment->applyEffect(slots[column].zombie.get());
        }
    }

    void battle(Hero& plantHero, Hero& zombieHero) {
        for (auto& slot : slots) {
            if (slot.plant) {
                if (slot.zombie) {
                    DamagePackage plantDamage(slot.plant->strength);
                    DamagePackage zombieDamage(slot.zombie->strength);

                    if (slot.environment) {
                        slot.environment->modifyDamage(zombieDamage, slot.zombie.get());
                    }

                    slot.plant->attack(slot.zombie.get(), plantDamage);
                    slot.zombie->attack(slot.plant.get(), zombieDamage);

                    if (slot.plant->markedForDeath) {
                        slot.plant->health = 0;
                        slot.plant.reset();
                    }
                    if (slot.zombie->markedForDeath) {
                        slot.zombie->health = 0;
                        slot.zombie.reset();
                    }
                } else {
                    plantHero.takeDamage(slot.plant->strength);
                }
            }
            if (slot.zombie && !slot.plant) {
                DamagePackage zombieDamage(slot.zombie->strength);
                if (slot.environment) {
                    slot.environment->modifyDamage(zombieDamage, slot.zombie.get());
                }
                plantHero.takeDamage(zombieDamage.getDamage());
            }
        }
    }

private:
    std::vector<Slot> slots{5}; // Assume 5 columns for simplicity
};

#endif // BATTLEFIELD_HPP
