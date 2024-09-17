#include "logger.h"

using namespace logger;

Logger::Logger(const std::string &filename) {
    logFile.open(filename, std::ios::app);  // Open file in append mode
    if (!logFile.is_open())
        std::cerr << "Unable to open log file: " << filename << std::endl;

}

Logger::~Logger() {
    if (logFile.is_open())
        logFile.close();

}

void Logger::log(const std::string &message) {
    if (logFile.is_open())
        logFile << getCurrentTime() << " - " << message << std::endl;
}

std::string Logger::getCurrentTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char timeStr[20];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", ltm);
    return std::string(timeStr);
}
