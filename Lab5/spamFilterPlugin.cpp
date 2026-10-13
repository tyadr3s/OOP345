#include "spamFilterPlugin.h"
#include "message.h"
#include <fstream>
#include <stdexcept>

namespace seneca {

    SpamFilterPlugin::SpamFilterPlugin(const char* filename) {
        std::ifstream file(filename);

        if (!file) {
            throw std::runtime_error("Cannot open spam file");
        }
        std::string word;

        while (m_keywordCount < 100 && std::getline(file, word)) {
            if (!word.empty()) {
                m_keywords[m_keywordCount] = word;
                m_keywordCount++;
            }
        }
    }
    
    void SpamFilterPlugin::operator()(Message& msg) {
        for (size_t i = 0; i < m_keywordCount; i++) {
            if (msg.m_subject.find(m_keywords[i]) != std::string::npos) {
                msg.m_subject = "[SPAM] " + msg.m_subject;
                m_spamCount++;
                break;
            }
        }
    }

    void SpamFilterPlugin::showStats() const {
        std::cout << "[Spam Filter Plugin] Identified "<< m_spamCount << " spam messages." << std::endl;
    }

}
