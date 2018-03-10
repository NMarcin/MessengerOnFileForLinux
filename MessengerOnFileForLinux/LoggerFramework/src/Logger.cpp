#include "Logger.hpp"

#include <iostream>

Logger::Logger(SavingMode mode)
                : savingMode(mode)
{
    //NOOP
}

Logger::~Logger()
{
    //NOOP
}

void Logger::info(const char* logData)
{
    writeToFile(logData);

	if (SavingMode::withConsole == savingMode)
    {
        writeToConsole(logData);
    }
}

void Logger::writeToFile(const char* log)
{
    FILE* logFile;
    logFile = fopen("Logger_default.txt", "a");
    if (!logFile)
    {
        std::cout << "logFile open failed!" << std::endl;
        exit(1);
    }

    fprintf(logFile, "%s %s \t %s\n", __DATE__, __TIME__, log);

    fclose(logFile);
}

void Logger::writeToConsole(const char* log)
{
    fprintf(stdout, "\n%s %s \t %s\n", __DATE__, __TIME__, log);
}
