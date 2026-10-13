/*
Name: Carlos Andres Ramirez Moreno
Seneca Email: caramirez-moreno@myseneca.ca
Student ID: 120847256
Date: October 12, 2026

I declare that this submission is the result of my own work
and I only copied the code that my professor provided to
complete my assignments. This submitted piece of work has
not been shared with any other student or 3rd party content
provider.
*/

#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H
#include <iostream>
#include "characterTpl.h"
#include "abilities.h"
#include "weapons.h"

namespace seneca{

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>class Rogue : public CharacterTpl<T>{
        int m_baseDefense{};
        int m_baseAttack{};
        FirstAbility_t m_firstAbility{};
        SecondAbility_t m_secondAbility{};
        Dagger m_weapon{};
    public:
        Rogue(const char* name, int maxHealth, int attack, int defense);
        int getAttackAmnt() const override;
        int getDefenseAmnt() const override;
        Character* clone() const override;
        void attack(Character* enemy) override;
        void takeDamage(int damage) override;
    };

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    Rogue<T, FirstAbility_t, SecondAbility_t>::Rogue(const char* name, int maxHealth, int attack, int defense): CharacterTpl<T>(name, maxHealth){
        m_baseAttack = attack;
        m_baseDefense = defense;
    }

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    int Rogue<T, FirstAbility_t, SecondAbility_t>::getAttackAmnt()const{
        double weapon = static_cast<double>(m_weapon);
        return static_cast<int>(m_baseAttack + 2 * weapon);
    }

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    int Rogue<T, FirstAbility_t, SecondAbility_t>::getDefenseAmnt()const{
        return m_baseDefense;
    }

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    Character* Rogue<T, FirstAbility_t, SecondAbility_t>::clone()const{
        return new Rogue<T, FirstAbility_t, SecondAbility_t>(*this);
    }

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    void Rogue<T, FirstAbility_t, SecondAbility_t>::attack(Character* enemy){
        std::cout << this->getName() << " is attacking "<< enemy->getName() << ".\n";
        m_firstAbility.useAbility(this);
        m_secondAbility.useAbility(this);

        int damage = this->getAttackAmnt();

        m_firstAbility.transformDamageDealt(damage);
        m_secondAbility.transformDamageDealt(damage);

        std::cout << "    Rogue deals " << damage << " melee damage!\n";

        enemy->takeDamage(damage);
    }

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    void Rogue<T, FirstAbility_t, SecondAbility_t>::takeDamage(int damage){
        std::cout << this->getName() << " is attacked for " << damage << " damage.\n";

        int defense = this->getDefenseAmnt();
        
        std::cout << "    Rogue has a defense of " << defense << ". Reducing damage received.\n";
        
        damage -= defense;
        if (damage < 0) {
            damage = 0;
        }
        m_firstAbility.transformDamageReceived(damage);
        m_secondAbility.transformDamageReceived(damage);
        CharacterTpl<T>::takeDamage(damage);
    }
}
#endif
