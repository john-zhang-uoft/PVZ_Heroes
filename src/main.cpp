#include "game/CardFactory.hpp"
#include "game/Battlefield.hpp"
#include "game/Observer.hpp"
#include "game/Hero.hpp"

class GameObserver : public Observer {
public:
    void onNotify(const Event& event) override {
        if (event.getType() == "DamageEvent") {
            const DamageEvent& damageEvent = static_cast<const DamageEvent&>(event);
            std::cout << damageEvent.source << " dealt " << damageEvent.damage
                      << " damage to " << damageEvent.target << std::endl;
        } else if (event.getType() == "DeathEvent") {
            const DeathEvent& deathEvent = static_cast<const DeathEvent&>(event);
            std::cout << deathEvent.name << " has died." << std::endl;
        }
    }
};

int main() {
    // Create heroes
    Hero plantHero("Green Shadow");
    Hero zombieHero("Super Brainz");

    // Register plant and zombie cards
    CardFactory::instance().registerCard("Plant", []() -> std::unique_ptr<Card> {
        auto card = std::make_unique<Plant>();
        card->name = "Peashooter";
        card->strength = 2;
        card->health = 3;
        card->cost = 1;
        return card;
    });
    CardFactory::instance().registerCard("Zombie", []() -> std::unique_ptr<Card> {
        auto card = std::make_unique<Zombie>();
        card->name = "Basic Zombie";
        card->strength = 1;
        card->health = 4;
        card->cost = 1;
        return card;
    });

    // Register special zombie card
    CardFactory::instance().registerCard("SpecialZombie", []() -> std::unique_ptr<Card> {
        auto card = std::make_unique<SpecialZombie>();
        card->name = "Buffed Zombie";
        card->strength = 2;
        card->health = 5;
        card->cost = 2;
        return card;
    });

    // Register deathtouch zombie card
    CardFactory::instance().registerCard("DeathtouchZombie", []() -> std::unique_ptr<Card> {
        auto card = std::make_unique<Zombie>();
        card->name = "Deathtouch Zombie";
        card->strength = 1;
        card->health = 1;
        card->cost = 1;
        card->deathtouch = true;
        return card;
    });

    // Register double damage environment
    CardFactory::instance().registerCard("DoubleDamageEnvironment", []() -> std::unique_ptr<Card> {
        auto card = std::make_unique<DoubleDamageEnvironment>();
        card->name = "Double Damage Environment";
        card->cost = 2;
        return card;
    });

    // Create battlefield and observer
    BattleField battlefield;
    auto observer = std::make_shared<GameObserver>();
    battlefield.addObserver(observer);

    // Add cards to battlefield
    auto plantCard = CardFactory::instance().createCard("Plant");
    auto deathtouchZombieCard = CardFactory::instance().createCard("DeathtouchZombie");
    dynamic_cast<Fighter*>(plantCard.get())->addObserver(observer);
    dynamic_cast<Zombie*>(deathtouchZombieCard.get())->addObserver(observer);

    battlefield.addPlant(0, std::unique_ptr<Fighter>(dynamic_cast<Fighter*>(plantCard.release())));
    battlefield.addZombie(0, std::unique_ptr<Fighter>(dynamic_cast<Fighter*>(deathtouchZombieCard.release())));

    // Add environment to battlefield
    auto environmentCard = CardFactory::instance().createCard("DoubleDamageEnvironment");
    battlefield.addEnvironment(0, std::unique_ptr<Environment>(dynamic_cast<Environment*>(environmentCard.release())));

    // Execute battle phase
    battlefield.battle(plantHero, zombieHero);

    return 0;
}