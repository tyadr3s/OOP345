#include "dictionary.h"
#include "settings.h"
#include <fstream>
#include <iostream>
namespace seneca{

    PartOfSpeech getPartOfSpeech(const std::string& pos){
        if (pos == "n." || pos == "n. pl.") return PartOfSpeech::Noun;
        else if (pos == "pron.") return PartOfSpeech::Pronoun;
        else if (pos == "a.") return PartOfSpeech::Adjective;
        else if (pos == "adv.") return PartOfSpeech::Adverb;
        else if (pos == "v." || pos == "v. i." || pos == "v. t." || pos == "v. t. & i.") return PartOfSpeech::Verb;
        else if (pos == "prep.") return PartOfSpeech::Preposition;
        else if (pos == "conj.") return PartOfSpeech::Conjunction;
        else if (pos == "interj.") return PartOfSpeech::Interjection;

        return PartOfSpeech::Unknown;
    }

    std::string getPartOfSpeechName(PartOfSpeech pos){
        if (pos == PartOfSpeech::Noun) return "noun";
        else if (pos == PartOfSpeech::Pronoun) return "pronoun";
        else if (pos == PartOfSpeech::Adjective) return "adjective";
        else if (pos == PartOfSpeech::Adverb) return "adverb";
        else if (pos == PartOfSpeech::Verb) return "verb";
        else if (pos == PartOfSpeech::Preposition) return "preposition";
        else if (pos == PartOfSpeech::Conjunction) return "conjunction";
        else if (pos == PartOfSpeech::Interjection) return "interjection";

        return "";
    }


    Dictionary::Dictionary(const char* filename){
        std::ifstream file(filename);

        if (!file){
            return;
        }

        std::string line;

        while (std::getline(file, line)){
            m_size++;
        }

        m_words = new Word[m_size];

        file.clear();
        file.seekg(0);

        size_t index = 0;

        while (std::getline(file, line)){

            size_t firstComma = line.find(',');
            size_t secondComma = line.find(',', firstComma + 1);

            m_words[index].m_word = line.substr(0, firstComma);

            std::string pos = line.substr(firstComma + 1, secondComma - firstComma - 1);

            m_words[index].m_pos = getPartOfSpeech(pos);

            m_words[index].m_definition = line.substr(secondComma + 1);

            index++;
        }
    }


    Dictionary::Dictionary(const Dictionary& source){
        m_size = source.m_size;

        if (source.m_words != nullptr){
            m_words = new Word[m_size];

            for (size_t i = 0; i < m_size; i++) {
                m_words[i] = source.m_words[i];
            }
        }
    }


    Dictionary& Dictionary::operator=(const Dictionary& source){
        if (this != &source){
            delete[] m_words;

            m_words = nullptr;
            m_size = source.m_size;

            if (source.m_words != nullptr){
                m_words = new Word[m_size];

                for (size_t i = 0; i < m_size; i++) {
                    m_words[i] = source.m_words[i];
                }
            }
        }
        return *this;
    }


    Dictionary::Dictionary(Dictionary&& source) {
        m_words = source.m_words;
        m_size = source.m_size;

        source.m_words = nullptr;
        source.m_size = 0;
    }


    Dictionary& Dictionary::operator=(Dictionary&& source){

        if (this != &source){

            delete[] m_words;

            m_words = source.m_words;
            m_size = source.m_size;

            source.m_words = nullptr;
            source.m_size = 0;
        }
        return *this;
    }


    Dictionary::~Dictionary() {
        delete[] m_words;
    }
    
    void Dictionary::searchWord(const char* word){
        
        bool found = false;
        
        for (size_t i = 0; i < m_size; i++){
            
            if (m_words[i].m_word == word){
                
                if (found == false) {
                    
                    std::cout << word << " - ";
                    found = true;
                }
                
                else{
                    for (size_t j = 0; j < m_words[i].m_word.length(); j++) {
                        std::cout << " ";
                    }
                    std::cout << " - ";
                }
                
                if (g_settings.m_verbose == true && m_words[i].m_pos != PartOfSpeech::Unknown){
                    std::cout << "(" << getPartOfSpeechName(m_words[i].m_pos) << ") ";
                }
                
                std::cout << m_words[i].m_definition << std::endl;
                
                if (g_settings.m_show_all == false) {
                    return;
                }
            }
        }
        
        if (found == false) {
            std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
        }
    }

}