/*
Name: Carlos Andres Ramirez Moreno
Seneca Email: caramirez-moreno@myseneca.ca
Student ID: 120847256
Date: October 13, 2026

I declare that this submission is the result of my own work
and I only copied the code that my professor provided to
complete my assignments. This submitted piece of work has
not been shared with any other student or 3rd party content
provider.
*/

#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include <iostream>
#include "characterTpl.h"
#include "abilities.h"
#include "weapons.h"
namespace seneca{

    template <typename T, typename Ability_t, typename Weapon_t> class Barbarian : public CharacterTpl<T>{
        int m_baseDefense{};
        int m_baseAttack{};
        Ability_t m_ability{};
        Weapon_t m_weapon[2]{};

    public:
        Barbarian(const char* name, int maxHealth,int attack, int defense, Weapon_t firstWeapon, Weapon_t secondWeapon);
        int getAttackAmnt() const override;
        int getDefenseAmnt() const override;
        Character* clone() const override;
        void attack(Character* enemy) override;
        void takeDamage(int dmg) override;
    };

    template <typename T, typename Ability_t, typename Weapon_t>
    Barbarian<T, Ability_t, Weapon_t>::Barbarian( const char* name, int maxHealth, int attack, int defense, Weapon_t firstWeapon, Weapon_t secondWeapon) : CharacterTpl<T>(name, maxHealth){
        m_baseAttack = attack;
        m_baseDefense = defense;
        m_weapon[0] = firstWeapon;
        m_weapon[1] = secondWeapon;
    }

    template <typename T, typename Ability_t, typename Weapon_t>
    int Barbarian<T, Ability_t, Weapon_t>::getAttackAmnt() const{
        double first = static_cast<double>(m_weapon[0]);
        double second = static_cast<double>(m_weapon[1]);
        return static_cast<int>(m_baseAttack + first / 2 + second / 2);
    }

    template <typename T, typename Ability_t, typename Weapon_t>
    int Barbarian<T, Ability_t, Weapon_t>::getDefenseAmnt() const{
        return m_baseDefense;
    }

    template <typename T, typename Ability_t, typename Weapon_t>
    Character* Barbarian<T, Ability_t, Weapon_t>::clone() const{
        return new Barbarian<T, Ability_t, Weapon_t>(*this);
    }

    template <typename T, typename Ability_t, typename Weapon_t>
    void Barbarian<T, Ability_t, Weapon_t>::attack(Character* enemy){
        std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";

        m_ability.useAbility(this);
        int damage = this->getAttackAmnt();
        m_ability.transformDamageDealt(damage);

        std::cout << "    Barbarian deals " << damage << " melee damage!\n";

        enemy->takeDamage(damage);
    }

    template <typename T, typename Ability_t, typename Weapon_t>
    void Barbarian<T, Ability_t, Weapon_t>::takeDamage(int damage){
        
        std::cout << this->getName() << " is attacked for " << damage << " damage.\n";
        
        int defense = this->getDefenseAmnt();
        
        std::cout << "    Barbarian has a defense of " << defense << ". Reducing damage received.\n";
        
        damage -= defense;
        if (damage < 0) {
            damage = 0;
        }
        m_ability.transformDamageReceived(damage);
        CharacterTpl<T>::takeDamage(damage);
    }

}
#endif
