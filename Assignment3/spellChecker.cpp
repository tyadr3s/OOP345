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

#include "spellChecker.h"
#include <fstream>
#include <iomanip>
namespace seneca{

    SpellChecker::SpellChecker(const char* filename){
        std::ifstream file(filename);
        if(!file){
            throw "Bad file name!";
        }
        for(int i = 0; i < 6; i++){
            file >> m_badWords[i] >> m_goodWords[i];
        }
    }

    void SpellChecker::operator()(std::string& text){
        for (int i = 0; i < 6; i++){
            size_t pos = 0;
            while ((pos = text.find(m_badWords[i], pos)) != std::string::npos){
                text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                m_count[i]++;
                pos += m_goodWords[i].length();
            }
        }
    }

    void SpellChecker::showStatistics(std::ostream& out) const{
        for(int i = 0; i < 6; i++){
            out << std::right << std::setw(15) << m_badWords[i] << ": " << m_count[i] << " replacements\n";
        }
    }
}
