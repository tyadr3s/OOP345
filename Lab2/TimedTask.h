#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <iostream>
#include <string>
#include <chrono>

namespace seneca {

    class TimedTask {

        struct Task {
            std::string name;
            std::string units;
            std::chrono::steady_clock::duration duration;
        };

        int numTasks;
        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point endTime;

        Task tasks[10];

    public:
        TimedTask();

        void startClock();
        void stopClock();
        void addTask(const char* name);

        friend std::ostream& operator<<(std::ostream& os, const TimedTask& task);
    };

}

#endif