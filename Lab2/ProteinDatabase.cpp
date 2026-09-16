#include "ProteinDatabase.h"
#include <fstream>

namespace seneca {

    ProteinDatabase::ProteinDatabase() {

        ids = nullptr;
        sequences = nullptr;
        numProteins = 0;
    }


    ProteinDatabase::ProteinDatabase(const std::string& filename) {

        ids = nullptr;
        sequences = nullptr;
        numProteins = 0;

        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line)) {

            if (!line.empty() && line[0] == '>') {
                numProteins++;
            }
        }

        ids = new std::string[numProteins];
        sequences = new std::string[numProteins];

        file.clear();
        file.seekg(0);

        size_t current = 0;

        while (std::getline(file, line)) {

            if (!line.empty() && line[0] == '>') {

                size_t first = line.find('|');
                size_t second = line.find('|', first + 1);

                ids[current] =
                    line.substr(first + 1, second - first - 1);

                current++;
            }

            else if (!line.empty()) {

                sequences[current - 1] += line;
            }
        }
    }


    // Copy Constructor

    ProteinDatabase::ProteinDatabase(const ProteinDatabase& other) {

        ids = nullptr;
        sequences = nullptr;

        numProteins = other.numProteins;

        if (numProteins > 0) {

            ids = new std::string[numProteins];
            sequences = new std::string[numProteins];

            for (size_t i = 0; i < numProteins; i++) {

                ids[i] = other.ids[i];
                sequences[i] = other.sequences[i];
            }
        }
    }


    // Copy Assignment Operator

    ProteinDatabase& ProteinDatabase::operator=(
        const ProteinDatabase& other) {

        if (this != &other) {

            delete[] ids;
            delete[] sequences;

            ids = nullptr;
            sequences = nullptr;

            numProteins = other.numProteins;

            if (numProteins > 0) {

                ids = new std::string[numProteins];
                sequences = new std::string[numProteins];

                for (size_t i = 0; i < numProteins; i++) {

                    ids[i] = other.ids[i];
                    sequences[i] = other.sequences[i];
                }
            }
        }

        return *this;
    }


    // Move Constructor
    ProteinDatabase::ProteinDatabase(ProteinDatabase&& other) {

        ids = other.ids;
        sequences = other.sequences;
        numProteins = other.numProteins;

        other.ids = nullptr;
        other.sequences = nullptr;
        other.numProteins = 0;
    }


    // Move Assignment Operator
    ProteinDatabase& ProteinDatabase::operator=(
        ProteinDatabase&& other) {

        if (this != &other) {

            delete[] ids;
            delete[] sequences;

            ids = other.ids;
            sequences = other.sequences;
            numProteins = other.numProteins;

            other.ids = nullptr;
            other.sequences = nullptr;
            other.numProteins = 0;
        }

        return *this;
    }

    ProteinDatabase::~ProteinDatabase() {

        delete[] ids;
        delete[] sequences;
    }


    size_t ProteinDatabase::size() const {

        return numProteins;
    }


    std::string ProteinDatabase::operator[](size_t index) const {

        if (index < numProteins) {
            return sequences[index];
        }

        return "";
    }


    std::string ProteinDatabase::getUID(size_t index) const {

        if (index < numProteins) {
            return ids[index];
        }

        return "None";
    }

}