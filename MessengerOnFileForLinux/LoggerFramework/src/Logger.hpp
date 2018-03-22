#pragma once

#include <string>

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

    void info(std::string& logData) const;
    void info(const char * logData) const;

private:
    SavingMode savingMode_;
    const char* logSpace_;

    void writeToFile(const char* log) const;
    void writeToConsole(const char* log) const;
};
