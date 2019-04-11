#pragma once

#include <string>

class TerminalCommand
{
public:
    virtual bool doCommand() = 0;

    TerminalCommand(std::string command);
    virtual ~TerminalCommand() = default;

private:
    std::string _commandName;
    std::string _command;
};
