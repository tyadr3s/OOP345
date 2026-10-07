#include "shoppingCart.h"

namespace seneca {

    ShoppingCart::ShoppingCart( const std::string& m_name, int m_age, const Toy* toys[], size_t m_count) {
        this->name = m_name;
        this->age = m_age;
        this->count = m_count;
        this->toys = new const Toy*[count];
        
        for (size_t i = 0; i < count; i++) {
            this->toys[i] = new Toy(*toys[i]);
        }
    }

    ShoppingCart::ShoppingCart(const ShoppingCart& other) {
        name = other.name;
        age = other.age;
        count = other.count;
        
        toys = new const Toy*[count];
        
        for (size_t i = 0; i < count; i++) {
            toys[i] = new Toy(*other.toys[i]);
        }
    }

    ShoppingCart& ShoppingCart::operator=(const ShoppingCart& other){
        
        if (this != &other){
            for (size_t i = 0; i < count; i++) {
                delete toys[i];
            }
            
            delete[] toys;
            name = other.name;
            age = other.age;
            count = other.count;

            toys = new const Toy*[count];

            for (size_t i = 0; i < count; i++) {
                toys[i] = new Toy(*other.toys[i]);
            }
        }
        return *this;
    }
    
    ShoppingCart::~ShoppingCart() {
        for (size_t i = 0; i < count; i++) {
            delete toys[i];
        }
        delete[] toys;
    }

    ShoppingCart::ShoppingCart(ShoppingCart&& other){
        name = std::move(other.name);
        age = other.age;
        count = other.count;
        toys = other.toys;
        
        other.age = 0;
        other.count = 0;
        other.toys = nullptr;
    }
    
    ShoppingCart& ShoppingCart::operator=(ShoppingCart&& other) { 
        if (this != &other) {
            for (size_t i = 0; i < count; i++) {
                delete toys[i];
            }
            delete[] toys;

            name = std::move(other.name);
            age = other.age;
            count = other.count;
            toys = other.toys;

            other.age = 0;
            other.count = 0;
            other.toys = nullptr;
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const ShoppingCart& cart) {
        static size_t callCount = 0;
        callCount++;
        
        os << "--------------------------\n";
        
        if (cart.toys == nullptr) {
            os << "Order " << callCount << ": This shopping cart is invalid.\n";
            os << "--------------------------\n";
        }else{
            os << "Order " << callCount << ": Shopping for " << cart.name << " " << cart.age << " years old (" << cart.count << " toys)\n";
            os << "--------------------------\n";
            
            if (cart.count == 0) {
                os << "Empty shopping cart!\n";
            } else{
                for (size_t i = 0; i < cart.count; i++) {
                    os << *cart.toys[i];
                }
            }
            os << "--------------------------\n";
        }
        return os;
    }
}