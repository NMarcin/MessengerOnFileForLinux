#pragma once
#include <memory>
#include <string>

#include "TerminalCommand.hpp"
#include "Logger.hpp"
#include "LogSpace.hpp"
#include "SignalHandling.hpp"

enum class ChatStatus
{
    conversation,
    terminal
};

struct ChatInformation //TODO lepsze miejsce na to
{
    std::string _chatPath {};
    std::string _messageFlag {};
    std::string _interlocutorUsername {};
};

class TerminalFunctionality
{
public:
    bool runCommand(const std::string& command, std::shared_ptr<ChatInformation> chatInfo = nullptr);

    TerminalFunctionality(std::string chatFileWithPath, ChatStatus chatStatus, const SignalHandler& _signalHandler);
    TerminalFunctionality( const SignalHandler& _signalHandler);
    ~TerminalFunctionality() = default;

    TerminalFunctionality(TerminalFunctionality &&) = delete;
    TerminalFunctionality operator=(TerminalFunctionality &&) = delete;
    TerminalFunctionality(const TerminalFunctionality &) = delete;
    TerminalFunctionality operator=(const TerminalFunctionality &) = delete;

private:
    std::unique_ptr<TerminalCommand> _terminalCommand = nullptr;
    std::string _chatFileWithPath;
    ChatStatus _chatStatus;
    const SignalHandler& _signalHandler;

    Logger _log {LogSpace::TerminalFunctionality};
};
