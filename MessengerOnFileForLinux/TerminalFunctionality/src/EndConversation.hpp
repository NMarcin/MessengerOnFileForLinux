#pragma once

#include <TerminalCommand.hpp>
#include <TerminalFunctionality.hpp>

class EndConversation : public TerminalCommand
{
public:
    bool doCommand() override;

    EndConversation(std::string command, std::shared_ptr<ChatInformation> chatInfo);
    ~EndConversation();

private:
    std::shared_ptr<ChatInformation> chatInfo_;
};
