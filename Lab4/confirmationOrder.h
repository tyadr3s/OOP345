#ifndef SENECA_SHOPPINGCART_H
#define SENECA_SHOPPINGCART_H
#include <iostream>
#include <string>
#include <utility>
#include "toy.h"

namespace seneca {

    class ConfirmationOrder{
        const Toy** toys{};
        size_t count{};

    public:
        ConfirmationOrder();

        ConfirmationOrder(const ConfirmationOrder& other);
        ConfirmationOrder& operator=(const ConfirmationOrder& other);
        ~ConfirmationOrder();
        
        ConfirmationOrder(ConfirmationOrder&& other);
        ConfirmationOrder& operator=(ConfirmationOrder&& other);

        ConfirmationOrder& operator+=(const Toy& toy);
        ConfirmationOrder& operator-=(const Toy& toy);

        friend std::ostream& operator<<(std::ostream& os, const ConfirmationOrder& order);
    };
}
#endif