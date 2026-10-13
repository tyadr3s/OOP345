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

#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
#include "character.h"
#include <iostream>
namespace seneca{

    template <typename T>
    class CharacterTpl : public Character{
        int m_healthMax{};
        T m_health{};

    public:
        CharacterTpl(const char* name, int maxHealth): Character(name), m_healthMax(maxHealth){
            m_health = maxHealth;
        }
        void takeDamage(int damage) override{
            m_health -= damage;

            if (getHealth() <= 0){
                m_health = 0;
                std::cout << "    " << getName() << " has been defeated!\n";
            }else{
                std::cout << "    " << getName() << " took " << damage
                          << " damage, " << getHealth() << " health remaining.\n";
            }
        }
        int getHealth() const override {
            return static_cast<int>(m_health);
        }
        int getHealthMax() const override {
            return m_healthMax;
        }
        void setHealth(int newHealth) override {
            m_health = newHealth;
        }
        void setHealthMax(int maxHealth) override {
            m_healthMax = maxHealth;
            m_health = maxHealth;
        }
    };
}
#endif
