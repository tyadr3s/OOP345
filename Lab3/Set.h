#ifndef SENECA_SET_H
#define SENECA_SET_H

#include "Collection.h"
#include <cmath>

namespace seneca {

    template <typename T>
    class Set : public Collection<T, 100> {

    public:

        bool add(const T& item) override {

            for (unsigned int i = 0; i < this->size(); i++) {

                if ((*this)[i] == item) {
                    return false;
                }
            }

            return Collection<T, 100>::add(item);
        }
    };


    template <>
    bool Set<double>::add(const double& item) {

        for (unsigned int i = 0; i < this->size(); i++) {

            if (std::fabs((*this)[i] - item) <= 0.01) {
                return false;
            }
        }

        return Collection<double, 100>::add(item);
    }

}

#endif