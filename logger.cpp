#include "logger.h"

using namespace logger;


Logger::Logger(const std::string &filename) {
    fileName = filename;
    std::filesystem::resize_file(fileName.c_str(), 0);

    logFile.open(fileName.c_str(), std::ios::out | std::ios::app);  // Open file in append mode
    if (!logFile.is_open())
        std::cerr << "Unable to open log file: " << filename << std::endl;
}

Logger::~Logger() {
    if (logFile.is_open())
        logFile.close();

}

void Logger::log(const std::string &message) {
    std::lock_guard<std::mutex> guard(logMutex);

    if (logFile.is_open()){
        logFile << getCurrentTime() << " - " << message << "\n";
        logFile.flush();
    }
    return;
}

std::string Logger::getCurrentTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char timeStr[20];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d_%H-%M-%S", ltm);
    return std::string(timeStr);
}

void Logger::saveAsNewLog(){
    std::lock_guard<std::mutex> guard(logMutex);
    if (logFile.is_open()){
        std::string newLogFile = getCurrentTime() + "_Log.txt";

        std::filesystem::path originalFilePath(fileName);
        originalFilePath.make_preferred();
        std::filesystem::path newFilePath = originalFilePath.parent_path() / newLogFile;
        newFilePath.make_preferred();
        std::filesystem::copy_file(originalFilePath, newFilePath);
    }
    return;
}
