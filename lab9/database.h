#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <memory>

namespace seneca {

    enum class Err_Status {
        Err_Success,
        Err_NotFound,
        Err_OutOfMemory
    };

    template <typename T>
    class Database {
        int count = 0;
        std::string keys[20];
        T values[20]{};
        std::string fileName;

        inline static std::shared_ptr<Database<T>> db = nullptr;

        Database(const std::string& name) {
            std::cout << "[" << this << "] Database(const std::string&)\n";

            fileName = name;
            std::ifstream file(name);

            while (count < 20 && file >> keys[count] >> values[count]) {

                for (char& c : keys[count]) {
                    if (c == '_') {
                        c = ' ';
                    }
                }

                encryptDecrypt(values[count]);
                count++;
            }
        }

        Database(const Database&) = delete;
        Database& operator=(const Database&) = delete;

        void encryptDecrypt(T& value) {}

    public:

        static std::shared_ptr<Database<T>> getInstance(const std::string& name) {
            if (db == nullptr) {
                db = std::shared_ptr<Database<T>>(new Database<T>(name));
            }

            return db;
        }

        Err_Status GetValue(const std::string& key, T& value) {
            for (int i = 0; i < count; i++) {
                if (keys[i] == key) {
                    value = values[i];
                    return Err_Status::Err_Success;
                }
            }

            return Err_Status::Err_NotFound;
        }

        Err_Status SetValue(const std::string& key, const T& value) {
            if (count == 20) {
                return Err_Status::Err_OutOfMemory;
            }

            keys[count] = key;
            values[count] = value;
            count++;

            return Err_Status::Err_Success;
        }

        ~Database() {
            std::cout << "[" << this << "] ~Database()\n";

            std::ofstream file(fileName + ".bkp.txt");

            for (int i = 0; i < count; i++) {
                T temp = values[i];
                encryptDecrypt(temp);

                file << std::left << std::setw(25) << keys[i]
                     << " -> " << temp << '\n';
            }
        }
    };

    template <>
    inline void Database<std::string>::encryptDecrypt(std::string& value) {
        const char secret[] = "secret encryption key";

        for (char& c : value) {
            for (int i = 0; secret[i] != '\0'; i++) {
                c = c ^ secret[i];
            }
        }
    }

    template <>
    inline void Database<long long>::encryptDecrypt(long long& value) {
        const char secret[] = "super secret encryption key";
        char* data = reinterpret_cast<char*>(&value);

        for (size_t i = 0; i < sizeof(value); i++) {
            for (int j = 0; secret[j] != '\0'; j++) {
                data[i] = data[i] ^ secret[j];
            }
        }
    }

}

#endif
