#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "game/Event.hpp"
#include <vector>
#include <memory>

class Observer {
public:
    virtual void onNotify(const Event& event) = 0;
    virtual ~Observer() = default;
};

class Subject {
public:
    void addObserver(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    void notify(const Event& event) {
        for (auto& observer : observers) {
            observer->onNotify(event);
        }
    }

private:
    std::vector<std::shared_ptr<Observer>> observers;
};

#endif // OBSERVER_HPP
