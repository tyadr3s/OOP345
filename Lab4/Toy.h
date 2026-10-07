#ifndef SENECA_TOY_H
#define SENECA_TOY_H

#include <iostream>
#include <string>

namespace seneca {

    class Toy{
        int id{};
        std::string name{};
        int quantity{};
        double price{};
        double HST = {0.13};
    public:  
        Toy();
        Toy(const std::string& toy);
        void update(int numItems);
        friend std::ostream& operator<<(std::ostream& os, const Toy& toy);

    };
}

#endif