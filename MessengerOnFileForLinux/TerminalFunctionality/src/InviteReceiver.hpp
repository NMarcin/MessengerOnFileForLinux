#pragma once

#include "TerminalFunctionality.hpp"
#include "TerminalControl.hpp"
#include "Logger.hpp"
#include "LogSpace.hpp"

class InviteReceiver : public TerminalCommand
{
public:
    bool doCommand() const override;

    InviteReceiver(std::string command, std::shared_ptr<ChatInformation> chatInfo, const SignalHandler& signalHandler);
    ~InviteReceiver() = default;

    InviteReceiver(InviteReceiver &&) = delete;
    InviteReceiver operator=(InviteReceiver &&) = delete;
    InviteReceiver(const InviteReceiver &) = delete;
    InviteReceiver operator=(const InviteReceiver &) = delete;

private:
    std::shared_ptr<ChatInformation> _chatInfo;
    const SignalHandler& _signalHandler;

    Logger _log {LogSpace::TerminalFunctionality};
};
