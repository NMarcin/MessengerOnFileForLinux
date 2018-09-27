#pragma once

#include <TerminalFunctionality.hpp>
#include <TerminalControl.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>

class InviteReceiver : public TerminalCommand
{
public:
    bool doCommand();

    InviteReceiver(std::string command, std::shared_ptr<ChatInformation> chatInfo);
    ~InviteReceiver();

private:
    std::string command_;
    std::shared_ptr<ChatInformation> chatInfo_;
    Logger log_ {LogSpace::TerminalFunctionality};
};

