#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include "Pair.h"

namespace seneca{

    template <typename T, unsigned int CAPACITY>
    class Collection {

        T items[CAPACITY]{};
        unsigned int count{};
        static T defaultValue;

    public:

        unsigned int size()const{
            return count;
        }

        void display(std::ostream& os = std::cout)const{

            os << "----------------------\n";
            os << "| Collection Content |\n";
            os << "----------------------\n";

            for (unsigned int i = 0; i < count; i++){
                os << items[i] << '\n';
            }

            os << "----------------------\n";
        }

        virtual bool add(const T& item){

            if (count < CAPACITY) {
                items[count] = item;
                count++;

                return true;
            }

            return false;
        }

        T operator[](unsigned int index) const{

            if (index < count) {
                return items[index];
            }

            return defaultValue;
        }

        virtual ~Collection() {
        }
    };


    template <typename T, unsigned int CAPACITY>
    T Collection<T, CAPACITY>::defaultValue{};


    template <>
    Pair Collection<Pair, 100>::defaultValue("No Key", "No Value");

}

#endif