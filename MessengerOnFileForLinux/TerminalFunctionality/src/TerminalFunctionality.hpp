#pragma once
#include <memory>
#include <string>
#include <TerminalCommand.hpp>

class TerminalControl;

class TerminalFunctionality
{
public:
    bool runCommand(std::string command, TerminalControl* x = nullptr);

    TerminalFunctionality(std::string chatFileWithPath);
    TerminalFunctionality() = default;
    ~TerminalFunctionality();

private:
    std::unique_ptr<TerminalCommand> terminalCommand_ = nullptr;
    std::string chatFileWithPath_;
};
