#include "timeMonitor.h"
namespace seneca{

    void TimeMonitor::startEvent(const char* name){
        m_name = name;
        m_startTime = std::chrono::steady_clock::now();
    }

    Event TimeMonitor::stopEvent(){
        auto endTime = std::chrono::steady_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>
            (endTime - m_startTime);

        Event event(m_name.c_str(), duration);
        
        return event;
    }
}