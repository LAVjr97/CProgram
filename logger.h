#ifndef LOGGER_H
#define LOGGER_H
#include "main.h"

namespace logger{
    class Logger {
        public:
            Logger(const std::string &filename);
            ~Logger();

            void log(const std::string &message);

            // Get current time for timestamping log entries
            std::string getCurrentTime();

        private:
            std::mutex logMutex;

            std::ofstream logFile;
            std::string fileName;

    };
}

#endif // LOGGER_H
