#include "FoodOrder.h"
#include <iostream>
#include <cstring>

using namespace std;

double g_taxrate = 0.0;
double g_dailydiscount = 0.0;

namespace seneca {

    FoodOrder::FoodOrder(const FoodOrder& source) {

        strcpy(m_name, source.m_name);
        m_price = source.m_price;
        m_special = source.m_special;

        if (source.m_description){
            m_description = new char[strlen(source.m_description) + 1];
            strcpy(m_description, source.m_description);
        }
    }

    FoodOrder& FoodOrder::operator=(const FoodOrder& source){
        if (this != &source){
            strcpy(m_name, source.m_name);
            m_price = source.m_price;
            m_special = source.m_special;

            delete[] m_description;
            m_description = nullptr;

            if (source.m_description){
                m_description = new char[strlen(source.m_description) + 1];
                strcpy(m_description, source.m_description);
            }
        }

        return *this;
    }

    FoodOrder::~FoodOrder(){
        delete[] m_description;
    }

    void FoodOrder::read(istream& input){
        if (!input.good())
            return;

        char description[1000];
        char status{};

        input.getline(m_name, 10, ',');
        input.getline(description, 1000, ',');

        input >> m_price;
        input.ignore();

        input >> status;
        input.ignore(1000, '\n');

        delete[] m_description;

        m_description = new char[strlen(description) + 1];
        strcpy(m_description, description);
        if (status == 'Y'){
            m_special = true;
        }
        else{
            m_special = false;
        }
    }

    void FoodOrder::display() const {
        static size_t counter = 0;
        counter++;

        cout.setf(ios::left, ios::adjustfield);
        cout.width(2);
        cout << counter << ". ";

        if (m_name[0] == '\0') {
            cout << "No Order\n";
            return;
        }

        double priceWithTax = m_price * (1 + g_taxrate);

        cout.width(10);
        cout << m_name << "|";

        cout.width(25);
        cout << m_description << "|";

        cout.setf(ios::fixed, ios::floatfield);
        cout.precision(2);

        cout.width(12);
        cout << priceWithTax << "|";

        if (m_special) {
            cout.setf(ios::right, ios::adjustfield);
            cout.width(13);
            cout << priceWithTax - g_dailydiscount;
        }
        cout << '\n';
    }
}