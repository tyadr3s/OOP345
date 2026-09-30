#ifndef SENECA_PAIR_H
#define SENECA_PAIR_H

#include <iostream>
#include <string>

namespace seneca {

    class Pair
    {
        std::string m_key{};
        std::string m_value{};

    public:
        const std::string& getKey() {
            return m_key;
        }

        const std::string& getValue() {
            return m_value;
        }

        Pair() = default; // Allows creating an empty Pair

        Pair(const std::string& key, const std::string& value)
            : m_key{ key }, m_value{ value } {}

        bool operator==(const Pair& other) const; // Compares Pairs by key

        friend std::ostream& operator<<(std::ostream& os, const Pair& pair); // Allows printing a Pair
    };

}

#endif