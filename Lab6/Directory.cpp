
#include "Directory.h"
#include <iomanip>
#include <stdexcept>
#include <string>

namespace seneca {

    Directory::Directory(const std::string& name) {
        m_name = name;
    }

    Directory::~Directory() {
        for (Resource* item : m_contents) {
            delete item;
        }
    }

    void Directory::update_parent_path(const std::string& path) {
        m_parent_path = path;

        for (Resource* item : m_contents) {
            item->update_parent_path(this->path());
        }
    }

    NodeType Directory::type() const {
        return NodeType::DIR;
    }

    std::string Directory::path() const {
        return m_parent_path + m_name;
    }

    std::string Directory::name() const {
        return m_name;
    }

    int Directory::count() const {
        return static_cast<int>(m_contents.size());
    }

    size_t Directory::size() const {
        size_t total = 0;

        for (Resource* item : m_contents) {
            total += item->size();
        }

        return total;
    }

    Directory& Directory::operator+=(Resource* item) {
        for (Resource* file : m_contents) {
            if (file->name() == item->name()) {
                throw std::invalid_argument("Resource already exists!");
            }
        }

        m_contents.push_back(item);
        item->update_parent_path(path());

        return *this;
    }

    Resource* Directory::find(const std::string& name,
                              const std::vector<OpFlags>& flags) {

        for (Resource* item : m_contents) {
            if (item->name() == name) {
                return item;
            }
        }

        bool recursive = false;

        for (OpFlags flag : flags) {
            if (flag == OpFlags::RECURSIVE) {
                recursive = true;
            }
        }

        if (recursive) {
            for (Resource* item : m_contents) {
                if (item->type() == NodeType::DIR) {

                    Directory* folder = dynamic_cast<Directory*>(item);
                    Resource* result = folder->find(name, flags);

                    if (result != nullptr) {
                        return result;
                    }
                }
            }
        }

        return nullptr;
    }

    void Directory::remove(const std::string& name,
                           const std::vector<OpFlags>& flags) {

        bool recursive = false;

        for (OpFlags flag : flags) {
            if (flag == OpFlags::RECURSIVE) {
                recursive = true;
            }
        }

        for (size_t i = 0; i < m_contents.size(); i++) {

            Resource* item = m_contents[i];

            if (item->name() == name) {

                if (item->type() == NodeType::DIR && !recursive) {
                    throw std::invalid_argument(
                        name + " is a directory. Pass the recursive flag to delete directories.");
                }

                m_contents.erase(m_contents.begin() + i);
                delete item;
                return;
            }
        }

        throw std::string(name + " does not exist in " + m_name);
    }

    void Directory::display(std::ostream& os,
                            const std::vector<FormatFlags>& flags) const {

        bool longFormat = false;

        for (FormatFlags flag : flags) {
            if (flag == FormatFlags::LONG) {
                longFormat = true;
            }
        }

        os << "Total size: " << size() << " bytes\n";

        for (Resource* item : m_contents) {

            if (item->type() == NodeType::DIR) {
                os << "D | ";
            }
            else {
                os << "F | ";
            }

            os << std::left << std::setw(15)
               << item->name() << " |";

            if (longFormat) {

                std::string countText = "";

                if (item->count() != -1) {
                    countText = std::to_string(item->count());
                }

                std::string sizeText =
                    std::to_string(item->size()) + " bytes";

                os << " " << std::right << std::setw(2)
                   << countText << " | ";

                os << std::setw(10) << sizeText << " | ";
            }

            os << std::right << '\n';
        }
    }

}
