#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H

#include <string>

namespace seneca {

    class ProteinDatabase {

        std::string* ids;
        std::string* sequences;
        size_t numProteins;

    public:

        ProteinDatabase();
        ProteinDatabase(const std::string& filename);

        ProteinDatabase(const ProteinDatabase& other);
        ProteinDatabase& operator=(const ProteinDatabase& other);

        ProteinDatabase(ProteinDatabase&& other);
        ProteinDatabase& operator=(ProteinDatabase&& other);

        ~ProteinDatabase();

        size_t size() const;
        std::string operator[](size_t index) const;
        std::string getUID(size_t index) const;
    };

}

#endif