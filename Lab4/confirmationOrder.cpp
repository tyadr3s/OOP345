#include "confirmationOrder.h"

namespace seneca {

    ConfirmationOrder::ConfirmationOrder() {
    }

    ConfirmationOrder& ConfirmationOrder::operator+=(const Toy& toy){
        
        for (size_t i = 0; i < count; i++) {
            if (toys[i] == &toy) {
                return *this;
            }
        }
        
        const Toy** temp = new const Toy*[count + 1];
        
        for (size_t i = 0; i < count; i++) {
            temp[i] = toys[i];
        }
        
        temp[count] = &toy;
        delete[] toys;
        
        toys = temp;
        count++;
        
        return *this;
    }

    ConfirmationOrder& ConfirmationOrder::operator-=(const Toy& toy){
        
        for (size_t i = 0; i < count; i++) {
            if (toys[i] == &toy) {
                
                for (size_t j = i; j < count - 1; j++) {
                    toys[j] = toys[j + 1];
                }
                count--;
                break;
            }
        }
        return *this;
    }

    ConfirmationOrder::ConfirmationOrder(const ConfirmationOrder& other) {
        count = other.count;
        toys = new const Toy*[count];
        
        for (size_t i = 0; i < count; i++) {
            toys[i] = other.toys[i];
        }
    }

    ConfirmationOrder& ConfirmationOrder::operator=(const ConfirmationOrder& other) {
        if (this != &other) {
            delete[] toys;
            
            count = other.count;
            toys = new const Toy*[count];
            
            for (size_t i = 0; i < count; i++) {
                toys[i] = other.toys[i];
            }
        }
        return *this;
    }

    ConfirmationOrder::~ConfirmationOrder() {
        delete[] toys;
    }

    ConfirmationOrder::ConfirmationOrder(ConfirmationOrder&& other) {
        
        toys = other.toys;
        count = other.count;
        other.toys = nullptr;
        other.count = 0;
    }

    ConfirmationOrder& ConfirmationOrder::operator=(ConfirmationOrder && other) {
        if (this != &other) {
            delete[] toys;
            
            toys = other.toys;
            count = other.count;
            other.toys = nullptr;
            other.count = 0;
        }
        return *this;
    }
    
    std::ostream& operator<<(std::ostream& os, const ConfirmationOrder& order) {
        
        os << "--------------------------\n";
        os << "Confirmations to Send\n";
        os << "--------------------------\n";
        
        if (order.count == 0) {
            os << "There are no confirmations to send!\n";
        } else{
            for (size_t i = 0; i < order.count; i++){
                os << *order.toys[i];
            }
        }
        os << "--------------------------\n";
        return os;
    }

}