#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H

#include <iostream>

extern double g_taxrate;
extern double g_dailydiscount;

namespace seneca {
    class FoodOrder {
        char m_name[10]{};
        char* m_description{};
        double m_price{};
        bool m_special{};

    public:
        FoodOrder() = default;

        FoodOrder(const FoodOrder& source);
        FoodOrder& operator=(const FoodOrder& source);
        ~FoodOrder();

        void read(std::istream& input);
        void display() const;
    };
}

#endif