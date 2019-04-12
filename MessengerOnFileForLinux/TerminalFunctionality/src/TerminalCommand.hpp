#pragma once

#include <string>

class TerminalCommand
{
public:
    virtual bool doCommand() const = 0;

    TerminalCommand(std::string command);
    virtual ~TerminalCommand() = default;

protected:
    std::string _commandName;
    std::string _command;
};
