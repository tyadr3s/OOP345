#ifndef SENECA_VERIFYIDENTITYPLUGIN_H
#define SENECA_VERIFYIDENTITYPLUGIN_H

#include <string>
#include <cstddef>
#include "plugin.h"

namespace seneca {

    class VerifyIdentityPlugin : public Plugin {
        std::string m_trustedEmails[100];
        std::size_t m_trustedCount = 0;

    public:
        VerifyIdentityPlugin(const char* filename);

        void operator()(Message& msg) override;

        void showStats() const override;
    };

}

#endif
