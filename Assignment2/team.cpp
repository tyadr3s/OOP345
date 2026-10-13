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

#include "team.h"
#include <iostream>
#include <utility>
namespace seneca {

    Team::Team(const char* name){
        m_name = name;
    }

    Team::~Team(){
        for (std::size_t i = 0; i < m_count; i++){
            delete m_members[i];
        }
        delete[] m_members;
    }

    Team::Team(const Team& other){
        m_name = other.m_name;
        m_count = other.m_count;
        
        if(m_count > 0) {
            m_members = new Character*[m_count]{};

            for(std::size_t i = 0; i < m_count; i++){
                m_members[i] = other.m_members[i]->clone();
            }
        }
    }
    
    Team& Team::operator=(const Team& other){
        
        if (this != &other) {
            for (std::size_t i = 0; i < m_count; i++){
                delete m_members[i];
            }
            delete[] m_members;
            
            m_members = nullptr;
            m_count = 0;
            m_name = other.m_name;
            
            if (other.m_count > 0){
                m_members = new Character*[other.m_count]{};
                m_count = other.m_count;
                
                for (std::size_t i = 0; i < m_count; i++) {
                    m_members[i] = other.m_members[i]->clone();
                }
            }
        }
        return *this;
    }

    Team::Team(Team&& other){
        m_name = std::move(other.m_name);
        m_members = other.m_members;
        m_count = other.m_count;
        
        other.m_members = nullptr;
        other.m_count = 0;
    }

    Team& Team::operator=(Team&& other){
        if (this != &other) {
            for (std::size_t i = 0; i < m_count; i++) {
                delete m_members[i];
            }
            delete[] m_members;
            
            m_name = std::move(other.m_name);
            m_members = other.m_members;
            m_count = other.m_count;
            
            other.m_members = nullptr;
            other.m_count = 0;
        }
        return *this;
    }

    void Team::addMember(const Character* c){
        for (size_t i = 0; i < m_count; i++){
            if (m_members[i]->getName() == c->getName()){
                return;
            }
        }
        
        Character** temp = new Character*[m_count + 1];
        
        for (size_t i = 0; i < m_count; i++){
            temp[i] = m_members[i];
        }
        
        temp[m_count] = c->clone();
        delete[] m_members;
        m_members = temp;
        m_count++;
    }

    void Team::removeMember(const std::string& name){
        for (size_t i = 0; i < m_count; i++){
            if (m_members[i]->getName() == name){
                delete m_members[i];
                
                for (size_t j = i; j < m_count - 1; j++){
                    m_members[j] = m_members[j + 1];
                }
                
                m_members[m_count - 1] = nullptr;
                m_count--;
                
                return;
            }
        }
    }

    Character* Team::operator[](size_t index) const {
        if (index >= m_count) {
            return nullptr;
        }
        return m_members[index];
    }
    
    void Team::showMembers() const {
        if (m_count == 0) {
            std::cout << "No team.\n";
            return;
        }
        
        std::cout << "[Team] " << m_name << '\n';
        
        for (size_t i = 0; i < m_count; i++) {
            std::cout << "    " << i + 1 << ": "<< *m_members[i] << '\n';
        }
    }
}
