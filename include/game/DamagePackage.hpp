#ifndef DAMAGEPACKAGE_HPP
#define DAMAGEPACKAGE_HPP

class DamagePackage {
public:
    int baseDamage;
    bool doubleDamage;

    DamagePackage(int damage, bool doubleDamage = false) 
        : baseDamage(damage), doubleDamage(doubleDamage) {}

    int getDamage() const {
        return doubleDamage ? baseDamage * 2 : baseDamage;
    }
};

#endif // DAMAGEPACKAGE_HPP
