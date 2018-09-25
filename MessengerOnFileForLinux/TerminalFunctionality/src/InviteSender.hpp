#pragma once

#include <TerminalFunctionality.hpp>
#include <functional>
#include <TerminalControl.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>

class InviteSender : public TerminalCommand
{
public:
    bool doCommand();

    InviteSender(std::string command, std::shared_ptr<ChatInformation> chatInfo);
    ~InviteSender();

private:
    std::string command_;
    std::shared_ptr<ChatInformation> chatInfo_;
    Logger log_ {LogSpace::MessageFramework};
};

