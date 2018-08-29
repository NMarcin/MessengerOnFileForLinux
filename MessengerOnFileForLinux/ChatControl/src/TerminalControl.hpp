#pragma once

#include <Logger.hpp>
#include <LogSpace.hpp>
#include <ChatControl.hpp>
// nie dodane do kompilowania


class TerminalControl //: public ChatControl
{
public:
    bool waitingInTerminal();

private:
    void startConversation(const std::string& username, ChatRole chatRole);
    void startConversationAsInviter(const std::string& username);
    void startConversationAsRecipient(const std::string& username);

    std::string chatFileWithPath_;
    MessageFlag messageFlag_;

    Logger log{LogSpace::ChatFile};
};
