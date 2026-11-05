#include "Filesystem.h"
#include "File.h"

#include <fstream>
#include <stdexcept>
#include <string>

namespace seneca {

    std::string Filesystem::trim(const std::string& text) {
        size_t start = text.find_first_not_of(" \t\r\n");

        if (start == std::string::npos) {
            return "";
        }

        size_t end = text.find_last_not_of(" \t\r\n");

        return text.substr(start, end - start + 1);
    }

    Filesystem::Filesystem(const char* filename, const std::string& rootName) {
        std::ifstream file(filename);

        if (!file) {
            throw std::invalid_argument("File does not exist!");
        }

        m_root = new Directory(rootName);
        m_current = m_root;

        std::string line;

        while (std::getline(file, line)) {
            std::string path;
            std::string contents = "";

            size_t separator = line.find('|');

            if (separator != std::string::npos) {
                path = trim(line.substr(0, separator));
                contents = trim(line.substr(separator + 1));
            }
            else {
                path = trim(line);
            }

            if (path.empty()) {
                continue;
            }

            Directory* current = m_root;

            while (!path.empty()) {

                size_t slash = path.find('/');

                if (slash != std::string::npos) {

                    std::string folderName = path.substr(0, slash + 1);

                    Resource* existing = current->find(folderName);

                    if (existing == nullptr) {
                        Directory* folder = new Directory(folderName);

                        *current += folder;
                        current = folder;
                    }
                    else {
                        Directory* folder = dynamic_cast<Directory*>(existing);

                        if (folder == nullptr) {
                            throw std::invalid_argument("Invalid directory!");
                        }

                        current = folder;
                    }

                    path.erase(0, slash + 1);
                }
                else {
                    File* newFile = new File(path, contents);

                    *current += newFile;

                    path.clear();
                }
            }
        }
    }

    Filesystem::Filesystem(Filesystem&& other) noexcept {
        m_root = other.m_root;
        m_current = other.m_current;

        other.m_root = nullptr;
        other.m_current = nullptr;
    }

    Filesystem& Filesystem::operator=(Filesystem&& other) noexcept {
        if (this != &other) {

            delete m_root;

            m_root = other.m_root;
            m_current = other.m_current;

            other.m_root = nullptr;
            other.m_current = nullptr;
        }

        return *this;
    }

    Filesystem::~Filesystem() {
        delete m_root;
    }

    Filesystem& Filesystem::operator+=(Resource* item) {
        *m_current += item;

        return *this;
    }

    Directory* Filesystem::change_directory(const std::string& name) {

        if (name.empty()) {
            m_current = m_root;
            return m_current;
        }

        Resource* item = m_current->find(name);

        if (item == nullptr || item->type() != NodeType::DIR) {
            throw std::invalid_argument(
                "Cannot change directory! " + name + " not found!");
        }

        m_current = dynamic_cast<Directory*>(item);

        return m_current;
    }

    Directory* Filesystem::get_current_directory() const {
        return m_current;
    }

}
