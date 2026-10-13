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

#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H
#include <iostream>
#include "characterTpl.h"
#include "health.h"
#include "weapons.h"

namespace seneca{
    
    template <typename Weapon_t>
    class Archer : public CharacterTpl<SuperHealth>{
        int m_baseDefense{};
        int m_baseAttack{};
        Weapon_t m_weapon{};
        
        public:
        
        Archer(const char* name, int maxHealth, int attack,
            int defense, Weapon_t weapon);
            int getAttackAmnt() const override;
            int getDefenseAmnt() const override;  
            Character* clone() const override;
            void attack(Character* enemy) override;
            void takeDamage(int damage) override;
        };
        
        template <typename Weapon_t>
        Archer<Weapon_t>::Archer(const char* name, int maxHealth, int attack, int defense, Weapon_t weapon): CharacterTpl<SuperHealth>(name, maxHealth){
            m_baseAttack = attack;
            m_baseDefense = defense;
            m_weapon = weapon;
        }
        
        template <typename Weapon_t>
        int Archer<Weapon_t>::getAttackAmnt()const{
            return static_cast<int>(m_baseAttack * 1.3);
        }
        
        template <typename Weapon_t>
        int Archer<Weapon_t>::getDefenseAmnt()const{
            return static_cast<int>(m_baseDefense * 1.2);
        }
        
        template <typename Weapon_t>
        Character* Archer<Weapon_t>::clone()const{
            return new Archer<Weapon_t>(*this);
        }
        
        template <typename Weapon_t>
        void Archer<Weapon_t>::attack(Character* enemy){
            std::cout << this->getName() << " is attacking "<< enemy->getName() << ".\n";
            
            int damage = this->getAttackAmnt();
            
            std::cout << "    Archer deals " << damage<< " ranged damage!\n";
            
            enemy->takeDamage(damage);
        }
        
        template <typename Weapon_t>
        void Archer<Weapon_t>::takeDamage(int damage){
            
            std::cout << this->getName() << " is attacked for "<< damage << " damage.\n";
            
            int defense = this->getDefenseAmnt();
            
            std::cout << "    Archer has a defense of " << defense<< ". Reducing damage received.\n";
            
            damage -= defense;
            if (damage < 0) {
                damage = 0;
            }
            CharacterTpl<SuperHealth>::takeDamage(damage);
        }
}
#endif
