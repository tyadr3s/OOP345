/*
Name: Carlos Andres Ramirez Moreno
Seneca Email: caramirez-moreno@myseneca.ca
Student ID: 120847256
Date: November 18, 2026

I declare that this submission is the result of my own work
and I only copied the code that my professor provided to
complete my assignments. This submitted piece of work has
not been shared with any other student or 3rd party content
provider.
*/
#include "collection.h"
#include <algorithm>
#include <stdexcept>
#include "collection.h" 

namespace seneca{

    Collection::Collection(const std::string &name) : m_name(name){
    }

    Collection::~Collection(){
        for (auto item : m_items){
            delete item;
        }
    }

    const std::string &Collection::name() const{
        return m_name;
    }

    size_t Collection::size() const{
        return m_items.size();
    }

    void Collection::setObserver(void (*observer)(const Collection &, const MediaItem &)){
        m_observer = observer;
    }

    Collection &Collection::operator+=(MediaItem *item){
        for (auto media : m_items){
            if (media->getTitle() == item->getTitle()){
                delete item;
                return *this;
            }
        }
        m_items.push_back(item);

        if (m_observer != nullptr){
            m_observer(*this, *item);
        }
        return *this;
    }
    
    MediaItem* Collection::operator[](size_t idx) const {
        if (idx >= m_items.size()) {
            throw std::out_of_range("Bad index " + std::to_string(idx) + ". Collection has " + std::to_string(m_items.size()) + " items.");
        }
        return m_items[idx];
    }

    std::ostream& operator<<(std::ostream& out, const Collection& col){
        for (size_t i = 0; i < col.size(); i++){
            out << *col[i];
        }
        return out;
    }

    void Collection::sort(const std::string& field){
        if (field == "title"){
            std::sort(m_items.begin(), m_items.end(), [](MediaItem* a, MediaItem* b){
                return a->getTitle() < b->getTitle();
            });
        }
        else if (field == "year") {
            std::sort(m_items.begin(), m_items.end(),[](MediaItem* a, MediaItem* b){
                return a->getYear() < b->getYear();
            });
        }
    }

        void Collection::removeQuotes(){

            std::for_each(m_items.begin(), m_items.end(),[](MediaItem* item){    
                std::string title = item->getTitle();
                std::string summary = item->getSummary();
                if (!title.empty() && title.front() == '"') {
                    title.erase(0, 1);
                }
                if (!title.empty() && title.back() == '"') {
                    title.pop_back();
                }
                if (!summary.empty() && summary.front() == '"') {
                    summary.erase(0, 1);
                }
                if (!summary.empty() && summary.back() == '"') {
                    summary.pop_back();
                }
                item->setTitle(title);
                item->setSummary(summary);
            });
    }
}
