
#include "verifyIdentityPlugin.h"
#include "message.h"
#include <fstream>
#include <iostream>

namespace seneca {

    VerifyIdentityPlugin::VerifyIdentityPlugin(const char* filename) {
        std::ifstream file(filename);

        if (!file) {
            throw std::runtime_error("Cannot open identities file");
        }

        std::string email;

        while (m_trustedCount < 100 && std::getline(file, email)) {
            if (!email.empty()) {
                m_trustedEmails[m_trustedCount] = email;
                m_trustedCount++;
            }
        }
    }
    
    void VerifyIdentityPlugin::operator()(Message& msg) {
        for (size_t i = 0; i < m_trustedCount; i++) {
            if (msg.m_fromAddress == m_trustedEmails[i]) {
                msg.m_subject = "[TRUSTED] " + msg.m_subject;
                break;
            }
        }
    }
    
    void VerifyIdentityPlugin::showStats() const {
        
        std::cout << "[Identity Checker Plugin] can validate identity for ";
        
        for (size_t i = 0; i < m_trustedCount; i++) {
            std::cout << m_trustedEmails[i];
            
            if (i < m_trustedCount - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }

}
