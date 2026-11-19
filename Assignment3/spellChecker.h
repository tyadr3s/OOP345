/*
Name: Carlos Andres Ramirez Moreno
Seneca Email: caramirez-moreno@myseneca.ca
Student ID: 120847256
Date: November 18, 2026

I declare that this submission is the result of my own work
and I only copied the code that my professor provided to
complete my assignments. This submitted piece of work has
not been shared with any other student or 3rd party content
provider.
*/
#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H
#include <iostream>
#include <string>
namespace seneca{

    class SpellChecker{
        std::string m_badWords[6];
        std::string m_goodWords[6];
        size_t m_count[6]{};
    public:
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const;
    };
}
#endif
