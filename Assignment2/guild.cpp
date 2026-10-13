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

#include "guild.h"
#include <iostream>
#include <utility>
namespace seneca {

    Guild::Guild(const char* name){
        m_name = name;
    }

    Guild::~Guild(){
        delete[] m_members;
    }

    Guild::Guild(const Guild& other){
        m_name = other.m_name;
        m_count = other.m_count;

        if (m_count > 0){
            m_members = new Character*[m_count];

            for (std::size_t i = 0; i < m_count; i++){
                m_members[i] = other.m_members[i];
            }
        }
    }

    Guild& Guild::operator=(const Guild& other){
        if (this != &other){
            delete[] m_members;

            m_members = nullptr;
            m_count = 0;
            m_name = other.m_name;

            if (other.m_count > 0){
                m_members = new Character*[other.m_count];
                m_count = other.m_count;

                for (std::size_t i = 0; i < m_count; i++){
                    m_members[i] = other.m_members[i];
                }
            }
        }
        return *this;
    }

    Guild::Guild(Guild&& other){
        m_name = std::move(other.m_name);
        m_members = other.m_members;
        m_count = other.m_count;
        other.m_members = nullptr;
        other.m_count = 0;
    }

    Guild& Guild::operator=(Guild&& other){
        if (this != &other) {
            delete[] m_members;

            m_name = std::move(other.m_name);
            m_members = other.m_members;
            m_count = other.m_count;
            other.m_members = nullptr;
            other.m_count = 0;
        }
        return *this;
    }

    void Guild::addMember(Character* c){

        if (c == nullptr) {
            return;
        }
        for (std::size_t i = 0; i < m_count; i++){
            if (m_members[i] == c){
                return;
            }
        }
        Character** temp = new Character*[m_count + 1];
        
        for (std::size_t i = 0; i < m_count; i++){
            temp[i] = m_members[i];
        }

        temp[m_count] = c;

        delete[] m_members;
        m_members = temp;
        m_count++;

        c->setHealthMax(c->getHealthMax() + 300);
    }

    void Guild::removeMember(const std::string& name){
        for (std::size_t i = 0; i < m_count; i++){
            if (m_members[i]->getName() == name){
                m_members[i]->setHealthMax(m_members[i]->getHealthMax() - 300);

                for (std::size_t j = i; j < m_count - 1; j++){
                    m_members[j] = m_members[j + 1];
                }

                m_members[m_count - 1] = nullptr;
                m_count--;
                return;
            }
        }
    }

    Character* Guild::operator[](std::size_t index)const{
        if (index >= m_count){
            return nullptr;
        }
        return m_members[index];
    }
    
    void Guild::showMembers()const{
        if (m_name.empty()){
            std::cout << "No guild.\n";
            return;
        }
        std::cout << "[Guild] " << m_name << '\n';
        
        for (std::size_t i = 0; i < m_count; i++){
            std::cout << "    " << i + 1 << ": "<< *m_members[i] << '\n';
        }
    }

}
