#pragma once

#include<TerminalCommand.hpp>

class LoggingOut : public TerminalCommand
{
public:
    bool doCommand() override;

    LoggingOut(std::string command);
    ~LoggingOut();

private:
};
