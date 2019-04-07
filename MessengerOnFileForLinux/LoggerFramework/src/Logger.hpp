#pragma once

#include <string>

enum class SavingMode
{
    fileOnly,
    withConsole
};

class Logger
{
public:
    Logger(const char* logSpace, SavingMode mode=SavingMode::fileOnly);
    ~Logger();

    void debug(std::string& logData) const;
    void debug(const char * logData) const;
    void function(std::string& logData) const;
    void function(const char * logData) const;
    void info(std::string& logData) const;
    void info(const char * logData) const;

private:
    SavingMode _savingMode;
    const char* _logSpace;

    void writeToFile(const char* log) const;
    void writeToConsole(const char* log) const;
};
