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

#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H
#include <iostream>
#include <string>
#include "mediaItem.h"
namespace seneca {
    class Movie : public MediaItem{

        Movie(const std::string& title, unsigned short year, const std::string& summary);

    public:
        void display(std::ostream& out) const override;
        static Movie* createItem(const std::string& strMovie);
    };
}
#endif
