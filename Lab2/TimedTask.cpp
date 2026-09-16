#include "TimedTask.h"
#include <iomanip>

namespace seneca {

    TimedTask::TimedTask() {
        numTasks = 0;
    }

    void TimedTask::startClock() {
        startTime = std::chrono::steady_clock::now();
    }

    void TimedTask::stopClock() {
        endTime = std::chrono::steady_clock::now();
    }

    void TimedTask::addTask(const char* name) {

        if (numTasks < 10) {

            tasks[numTasks].name = name;
            tasks[numTasks].units = "nanoseconds";

            tasks[numTasks].duration =
                std::chrono::duration_cast<std::chrono::nanoseconds>(
                    endTime - startTime
                );

            numTasks++;
        }
    }

    std::ostream& operator<<(std::ostream& os, const TimedTask& task) {

        os << "--------------------------\n";
        os << "Execution Times:\n";
        os << "--------------------------\n";

        for (int i = 0; i < task.numTasks; i++) {

            os << std::left << std::setw(21)
               << task.tasks[i].name;

            os << std::right << std::setw(13)
               << task.tasks[i].duration.count();

            os << " " << task.tasks[i].units << "\n";
        }

        os << "--------------------------\n";

        return os;
    }

}