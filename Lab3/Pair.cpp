#include "Pair.h"
#include <iomanip>

namespace seneca {

    bool Pair::operator==(const Pair& other) const {
        return m_key == other.m_key;
    }

    std::ostream& operator<<(std::ostream& os, const Pair& pair) {
        os << std::setw(20) << std::right << pair.m_key
           << ": " << pair.m_value;
        return os;
    }

}