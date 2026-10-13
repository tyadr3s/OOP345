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

#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include <string>
#include <cstddef>
#include "character.h"
namespace seneca {

    class Team{
        std::string m_name{};
        Character** m_members = nullptr;
        std::size_t m_count = 0;
    public:
        Team() = default;
        Team(const char* name);
        ~Team();

        Team(const Team& other);
        Team& operator=(const Team& other);
        
        Team(Team&& other);
        Team& operator=(Team&& other);

        void addMember(const Character* c);
        void removeMember(const std::string& name);
        void showMembers() const;

        Character* operator[](std::size_t index) const;
    };
}
#endif
