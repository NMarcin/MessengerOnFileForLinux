#pragma once

#include<TerminalCommand.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>

class LoggingOut : public TerminalCommand
{
public:
    bool doCommand() override;

    LoggingOut(std::string command);
    ~LoggingOut() = default;

private:
    Logger log_ {LogSpace::TerminalFunctionality};
};
