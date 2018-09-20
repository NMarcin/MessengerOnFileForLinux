#pragma once

#include <TerminalCommand.hpp>

class EndConversation : public TerminalCommand
{
public:
    bool doCommand() override;

    EndConversation(std::string command);
    ~EndConversation();

private:
    std::string chatFileWithPath_;
};
