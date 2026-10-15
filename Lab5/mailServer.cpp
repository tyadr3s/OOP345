#include "mailServer.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <utility>

namespace seneca {

    MailServer::MailServer(const char* name, const char* address) {
        m_userName = name;
        m_userAddress = address;
    }

    MailServer::~MailServer() {
        delete[] m_inbox;
    }
    
    MailServer::MailServer(const MailServer& other) {
        m_userName = other.m_userName;
        m_userAddress = other.m_userAddress;
        m_cnt = other.m_cnt;
        onNewMailArrived = other.onNewMailArrived;
        
        for (std::size_t i = 0; i < 2; i++) {
            m_plugins[i] = other.m_plugins[i];
        }
        
        if (m_cnt > 0) {
            m_inbox = new Message[m_cnt];
            for (std::size_t i = 0; i < m_cnt; i++) {
                m_inbox[i] = other.m_inbox[i];
            }
        }
    }
    
    MailServer& MailServer::operator=(const MailServer& other) {
        if (this != &other) {
            Message* newInbox = nullptr;
            
            if (other.m_cnt > 0) {
                newInbox = new Message[other.m_cnt];
                
                for (std::size_t i = 0; i < other.m_cnt; i++) {
                    newInbox[i] = other.m_inbox[i];
                }
            }
            delete[] m_inbox;
            m_inbox = newInbox;

            m_userName = other.m_userName;
            m_userAddress = other.m_userAddress;
            m_cnt = other.m_cnt;
            
            onNewMailArrived = other.onNewMailArrived;
            
            for (std::size_t i = 0; i < 2; i++) {
                m_plugins[i] = other.m_plugins[i];
            }
        }
        return *this;
    }

    MailServer::MailServer(MailServer&& other){
        m_userName = std::move(other.m_userName);
        m_userAddress = std::move(other.m_userAddress);
        
        m_inbox = other.m_inbox;
        m_cnt = other.m_cnt;
        
        onNewMailArrived = other.onNewMailArrived;
        
        for (std::size_t i = 0; i < 2; i++) {
            m_plugins[i] = other.m_plugins[i];
            other.m_plugins[i] = nullptr;
        }
        
        other.m_inbox = nullptr;
        other.m_cnt = 0;
        other.onNewMailArrived = nullptr;
    }
    
    MailServer& MailServer::operator=(MailServer&& other){
        if (this != &other) {
            delete[] m_inbox;
            
            m_userName = std::move(other.m_userName);
            m_userAddress = std::move(other.m_userAddress);
            
            m_inbox = other.m_inbox;
            m_cnt = other.m_cnt;
            
            onNewMailArrived = other.onNewMailArrived;
            
            for (std::size_t i = 0; i < 2; i++) {
                m_plugins[i] = other.m_plugins[i];
                other.m_plugins[i] = nullptr;
            }
            
            other.m_inbox = nullptr;
            other.m_cnt = 0;
            other.onNewMailArrived = nullptr;
        }
        return *this;
    }

    void MailServer::receiveMail(Message msg) {
        if (msg.m_toAddress != m_userAddress) {
            throw std::invalid_argument(msg.m_toAddress);
        }
        
        Message* newInbox = new Message[m_cnt + 1];
        
        for (std::size_t i = 0; i < m_cnt; i++) {
            newInbox[i] = m_inbox[i];
        }
        
        newInbox[m_cnt] = msg;
        
        delete[] m_inbox;
        
        m_inbox = newInbox;
        m_cnt++;
        
        for (int i = 0; i < 2; i++) {
            if (m_plugins[i] != nullptr) {
                (*m_plugins[i])(m_inbox[m_cnt - 1]);
            }
        }
        
        if (onNewMailArrived != nullptr) {
            onNewMailArrived(m_inbox[m_cnt - 1]);
        }
    
    
    }

    void MailServer::addPlugin(Plugin* thePlugin) {
        for (int i = 0; i < 2; i++) {
            if (m_plugins[i] == nullptr) {
                m_plugins[i] = thePlugin;
                break;
            }
        }
    }
    
    void MailServer::setObserver(void (*observer)(const Message&)) {
        onNewMailArrived = observer;
    }

    Message& MailServer::operator[](std::size_t idx) {
        if (idx >= m_cnt) {
            throw std::out_of_range("Index " + std::to_string(idx) + " is out of bounds");
        }
        return m_inbox[idx];
    }

    std::size_t MailServer::getInboxSize() const {
        return m_cnt;
    }

    void MailServer::showInbox() const {
        for (std::size_t i = 0; i < m_cnt; i++) {
            std::cout << std::right << std::setw(20) << m_inbox[i].m_fromName << "  "
            << std::left << std::setw(40) << m_inbox[i].m_fromAddress << "  "
            << std::setw(15) << m_inbox[i].m_date.substr(0, 10) << "  "<< m_inbox[i].m_subject << '\n';
        }
        std::cout << std::right;
    }

}