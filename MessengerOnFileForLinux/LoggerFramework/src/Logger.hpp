#pragma once

enum SavingMode
{
    fileOnly,
    withConsole
};

class Logger
{
public:
    Logger(const char* logSpace, SavingMode mode=SavingMode::fileOnly);
    ~Logger();

    void info(const char * logData);

private:
    SavingMode savingMode_;
    const char* logSpace_;

    void writeToFile(const char* log);
    void writeToConsole(const char* log);
};
