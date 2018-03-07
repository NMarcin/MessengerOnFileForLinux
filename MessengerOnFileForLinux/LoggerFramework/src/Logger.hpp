#pragma once


enum SavingMode
{
    fileOnly,
    withConsole
};

class Logger
{
public:

    Logger(SavingMode mode);
    ~Logger();

    void info(const char * logData);

private:

    SavingMode savingMode;

    void writeToFile(const char* log);
    void writeToConsole(const char* log);
};
