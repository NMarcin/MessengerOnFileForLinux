#include <iostream>

#include <Logger.hpp>

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

void Logger::info(const char* logData) const
{
    writeToFile(logData);

	if (SavingMode::withConsole == savingMode_)
    {
        writeToConsole(logData);
    }
}

void Logger::writeToConsole(const char* log) const
{
    fprintf(stdout, "\n%s %s %s \t %s\n", __DATE__, __TIME__, logSpace_, log);
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

    fprintf(logFile, "\n%s %s %s \t %s\n", __DATE__, __TIME__, logSpace_, log);

    fclose(logFile);
}
