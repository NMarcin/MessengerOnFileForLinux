#pragma once
#include <string>

class TerminalCommand
{
public:
    virtual bool doCommand() = 0;

    TerminalCommand(std::string command);
    virtual ~TerminalCommand() = default;

private:
    std::string commandName_;
    std::string command_;
};
