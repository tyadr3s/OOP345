#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H
#include <iostream>
#include "event.h"

namespace seneca{

    class Logger{

        Event* m_events{};
        size_t m_size{};

    public:

        Logger() = default;

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        
        Logger(Logger&& source);
        Logger& operator=(Logger&& source);

        ~Logger();

        void addEvent(const Event& event);

        friend std::ostream& operator<<(std::ostream& os, const Logger& logger);
    };

}

#endif