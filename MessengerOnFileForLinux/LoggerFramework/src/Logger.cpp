#include <Logger.hpp>

#include <iostream>

Logger::Logger(const char* logSpace, SavingMode mode)
                : savingMode_(mode)
                , logSpace_(logSpace)
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

	if (SavingMode::withConsole == savingMode_)
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

    fprintf(logFile, "\n%s %s %s \t %s\n", __DATE__, __TIME__, logSpace_, log);

    fclose(logFile);
}

void Logger::writeToConsole(const char* log)
{
    fprintf(stdout, "\n%s %s %s \t %s\n", __DATE__, __TIME__, logSpace_, log);
}
