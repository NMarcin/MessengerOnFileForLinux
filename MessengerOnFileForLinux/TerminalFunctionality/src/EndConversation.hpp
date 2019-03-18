#pragma once

#include <TerminalCommand.hpp>
#include <TerminalFunctionality.hpp>

class EndConversation : public TerminalCommand
{
public:
    bool doCommand() override;

    EndConversation(std::string command, std::shared_ptr<ChatInformation> chatInfo);
    ~EndConversation();

    EndConversation(EndConversation &&) = delete;
    EndConversation operator=(EndConversation &&) = delete;
    EndConversation(const EndConversation &) = delete;
    EndConversation operator=(const EndConversation &) = delete;

private:
    std::shared_ptr<ChatInformation> chatInfo_;
    Logger log_ {LogSpace::TerminalFunctionality};
};
