#include "ClasslessLogger.hpp"
#include <chrono>
#include <ctime>
#include <iostream>

void fileLog(const char * logData, const char * logSpace)
{
    FILE* logFile;
    logFile = fopen("Logger_default.txt", "a");
    if (!logFile)
    {
        std::cout << "logFile open failed!" << std::endl;
        exit(1);
    }

    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string timeAsString = ctime(&time);
    timeAsString.erase(timeAsString.end()-1);
    fprintf(logFile, "%s %s %s\n", timeAsString.c_str(), logSpace, logData);

    fclose(logFile);
}
