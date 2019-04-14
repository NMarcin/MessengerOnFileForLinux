#include <chrono>
#include <ctime>
#include <iostream>

#include "Logger.hpp"

Logger::Logger(const char* logSpace, SavingMode mode)
                : _savingMode(mode)
                , _logSpace(logSpace)
{
    //NOOP
}

Logger::~Logger()
{
    //NOOP
}

void Logger::debug(std::string& logData) const
{
    info(logData.c_str());
}

void Logger::debug(const char* logData) const
{
    info(logData);
}

void Logger::function(std::string& logData) const
{
    info(logData.c_str());
}

void Logger::function(const char* logData) const
{
    info(logData);
}

void Logger::info(std::string& logData) const
{
    info(logData.c_str());
}

void Logger::info(const char* logData) const
{
    writeToFile(logData);

    if (SavingMode::withConsole == _savingMode)
    {
        writeToConsole(logData);
    }
}

void Logger::writeToConsole(const char* log) const
{
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string timeAsString = ctime(&time);
    timeAsString.erase(timeAsString.end()-1);
    fprintf(stdout, "%s %s  %s\n", timeAsString.c_str(), _logSpace, log);
}

void Logger::writeToFile(const char* log) const
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
    fprintf(logFile, "%s %s %s\n", timeAsString.c_str(), _logSpace, log);

    fclose(logFile);
}
