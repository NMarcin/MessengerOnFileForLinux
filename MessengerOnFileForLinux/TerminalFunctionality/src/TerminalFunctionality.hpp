#pragma once
#include <memory>
#include <string>

#include <TerminalCommand.hpp>

enum class ChatStatus
{
    conversation,
    terminal
};

class TerminalFunctionality
{
public:
    bool runCommand(std::string command);

    TerminalFunctionality(std::string chatFileWithPath, ChatStatus chatStatus);
    TerminalFunctionality() = default;
    ~TerminalFunctionality() = default;

private:
    std::unique_ptr<TerminalCommand> terminalCommand_ = nullptr;
    std::string chatFileWithPath_;
    ChatStatus chatStatus_;
};
