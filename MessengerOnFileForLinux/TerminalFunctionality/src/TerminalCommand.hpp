#pragma once
#include <string>

class TerminalCommand
{
public:
    virtual bool doCommand() const = 0;

    TerminalCommand(std::string command);
    virtual ~TerminalCommand() = default;

private:
    const std::string commandName_;
    const std::string command_;
};
