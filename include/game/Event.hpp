#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Event {
public:
    virtual std::string getType() const = 0;
    virtual ~Event() = default;
};

class DamageEvent : public Event {
public:
    DamageEvent(const std::string& source, const std::string& target, int damage)
        : source(source), target(target), damage(damage) {}

    std::string getType() const override {
        return "DamageEvent";
    }

    std::string source;
    std::string target;
    int damage;
};

class DeathEvent : public Event {
public:
    DeathEvent(const std::string& name)
        : name(name) {}

    std::string getType() const override {
        return "DeathEvent";
    }

    std::string name;
};

#endif // EVENT_HPP
