#ifndef CARDFACTORY_HPP
#define CARDFACTORY_HPP

#include "game/Card.hpp"
#include <unordered_map>
#include <functional>

class CardFactory {
public:
    using CreateCardFunc = std::function<std::unique_ptr<Card>()>;

    static CardFactory& instance() {
        static CardFactory instance;
        return instance;
    }

    void registerCard(const std::string& type, CreateCardFunc func) {
        cardCreators[type] = func;
    }

    std::unique_ptr<Card> createCard(const std::string& type) {
        if (cardCreators.find(type) != cardCreators.end()) {
            return cardCreators[type]();
        }
        return nullptr;
    }

private:
    CardFactory() = default;
    std::unordered_map<std::string, CreateCardFunc> cardCreators;
};

#endif // CARDFACTORY_HPP
