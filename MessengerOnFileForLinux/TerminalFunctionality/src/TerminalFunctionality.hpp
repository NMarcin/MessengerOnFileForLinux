#pragma once
#include <memory>
#include <string>

#include <TerminalCommand.hpp>

class TerminalFunctionality
{
public:
    bool runCommand(std::string command);

    TerminalFunctionality();
    ~TerminalFunctionality();

private:
    std::unique_ptr<TerminalCommand> terminalCommand_;
};
