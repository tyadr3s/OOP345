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

#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H
#include <string>
#include <cstddef>
#include "character.h"
namespace seneca {

    class Guild {
        std::string m_name{};
        Character** m_members = nullptr;
        std::size_t m_count = 0;
    public:
        Guild() = default;
        Guild(const char* name);
        ~Guild();

        Guild(const Guild& other);
        Guild& operator=(const Guild& other);

        Guild(Guild&& other);
        Guild& operator=(Guild&& other);

        void addMember(Character* c);
        void removeMember(const std::string& name);
        void showMembers() const;

        Character* operator[](std::size_t index) const;
    };
}
#endif
