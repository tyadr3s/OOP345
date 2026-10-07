#ifndef SENECA_SHOPPINGCART_H
#define SENECA_SHOPPINGCART_H
#include <iostream>
#include <string>
#include "toy.h"

namespace seneca {

    class ShoppingCart {
        std::string name;
        int age {};
        const Toy** toys{};
        size_t count{};
        
        public:

        ShoppingCart();

        ShoppingCart(const std::string& name, int age, const Toy* toys[], size_t count);

        ShoppingCart(const ShoppingCart& other);
        ShoppingCart& operator=(const ShoppingCart& other);
        ~ShoppingCart();

        ShoppingCart(ShoppingCart&& other);
        ShoppingCart& operator=(ShoppingCart&& other);


        friend std::ostream& operator<<(std::ostream& os, const ShoppingCart& cart);
    };

}
#endif