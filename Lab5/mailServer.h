
#ifndef SENECA_MAILSERVER_H
#define SENECA_MAILSERVER_H

#include <string>
#include <cstddef>
#include "message.h"
#include "plugin.h"

namespace seneca {

    class MailServer {
        std::string m_userName;
        std::string m_userAddress;

        Message* m_inbox = nullptr;
        std::size_t m_cnt = 0;

        void (*onNewMailArrived)(const Message&) = nullptr;

        Plugin* m_plugins[2] = {nullptr, nullptr};

    public:
        MailServer(const char* name, const char* address);

        ~MailServer();
        MailServer(const MailServer& other);
        MailServer& operator=(const MailServer& other);
        MailServer(MailServer&& other);
        MailServer& operator=(MailServer&& other);

        void receiveMail(Message msg);
        void addPlugin(Plugin* thePlugin);
        void setObserver(void (*observer)(const Message&));

        Message& operator[](std::size_t idx);

        std::size_t getInboxSize() const;
        void showInbox() const;
    };

}

#endif
