
#ifndef SENECA_SPAMFILTERPLUGIN_H
#define SENECA_SPAMFILTERPLUGIN_H

#include <string>
#include <cstddef>
#include "plugin.h"

namespace seneca {

    class SpamFilterPlugin : public Plugin {
        std::string m_keywords[100];
        std::size_t m_keywordCount = 0;
        std::size_t m_spamCount = 0;

    public:
        SpamFilterPlugin(const char* filename);

        void operator()(Message& msg) override;

        void showStats() const override;
    };

}

#endif
