#include "toy.h"
#include <iomanip>

namespace seneca {

    Toy::Toy() {
    }

    Toy::Toy(const std::string& toy) {
        std::string temp = toy;
        
        size_t pos = temp.find(':');
        std::string token = temp.substr(0, pos);
        token.erase(0, token.find_first_not_of(' '));
        token.erase(token.find_last_not_of(' ') + 1);
        id = std::stoi(token);
        temp.erase(0, pos + 1);

        pos = temp.find(':');
        token = temp.substr(0, pos);
        token.erase(0, token.find_first_not_of(' '));
        token.erase(token.find_last_not_of(' ') + 1);
        name = token;
        temp.erase(0, pos + 1);
        
        pos = temp.find(':');
        token = temp.substr(0, pos);
        token.erase(0, token.find_first_not_of(' '));
        token.erase(token.find_last_not_of(' ') + 1);
        quantity = std::stoi(token);
        temp.erase(0, pos + 1);
        
        temp.erase(0, temp.find_first_not_of(' '));
        temp.erase(temp.find_last_not_of(' ') + 1);
        price = std::stod(temp);
    }

    void Toy::update(int numItems) {
        quantity = numItems;
    }

    std::ostream& operator<<(std::ostream& os, const Toy& toy) {
        auto oldFlags = os.flags();
        auto oldPrecision = os.precision();
        auto oldFill = os.fill();

        double subtotal = toy.quantity * toy.price;
        double tax = subtotal * toy.HST;
        double total = subtotal + tax;
        
        os << "Toy "
        << std::right << std::setfill('0') << std::setw(8) << toy.id
        << ": "
        << std::setfill('.') << std::setw(24) << toy.name
        << " "
        << std::setfill(' ') << std::setw(2) << toy.quantity
        << " items @ "
        << std::fixed << std::setprecision(2)
        << std::setw(6) << toy.price
        << "/item  subtotal: "
        << std::setw(7) << subtotal
        << "  tax: "
        << std::setw(6) << tax
        << "  total: "
        << std::setw(7) << total
        << std::endl;
        
        os.flags(oldFlags);
        os.precision(oldPrecision);
        os.fill(oldFill);
        
        return os;
    }

}