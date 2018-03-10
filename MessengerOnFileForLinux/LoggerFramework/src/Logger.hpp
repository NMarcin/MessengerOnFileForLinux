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
    Logger(SavingMode mode=SavingMode::fileOnly, std::string logSpace);
    ~Logger();

    void info(const char * logData);

private:
    SavingMode savingMode_;
    constexpr std::string logSpace_;

    void writeToFile(const char* log);
    void writeToConsole(const char* log);
};
