#pragma once
#include <memory>
#include <string>
#include <TerminalCommand.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>

enum class ChatStatus
{
    conversation,
    terminal
};

struct ChatInformation //TODO lepsze miejsce na to
{
    std::string chatPath_ {};
    std::string messageFlag_ {};
    std::string interlocutorUsername_ {};
};

class TerminalFunctionality
{
public:
    bool runCommand(std::string command, std::shared_ptr<ChatInformation> chatInfo = nullptr);

    TerminalFunctionality(std::string chatFileWithPath, ChatStatus chatStatus);
    TerminalFunctionality() = default;
    ~TerminalFunctionality() = default;

private:
    std::unique_ptr<TerminalCommand> terminalCommand_ = nullptr;
    std::string chatFileWithPath_;
    ChatStatus chatStatus_;

    Logger log_ {LogSpace::TerminalFunctionality};
};
