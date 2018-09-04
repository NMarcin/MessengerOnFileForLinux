#pragma once

#include <Logger.hpp>
#include <LogSpace.hpp>
#include <ChatData.hpp>
// nie dodane do kompilowania


class TerminalControl //: public ChatControl
{
public:
    bool waitingInTerminal();
    void startConversation(const std::string& username, ChatRole chatRole); // TO DO mwozniak to private, but temporary is here because GlobalVariables.hpp

private:
    void startConversationAsInviter(const std::string& username);
    void startConversationAsRecipient(const std::string& username);

    std::string chatFileWithPath_;
    MessageFlag messageFlag_;

    Logger log{LogSpace::ChatFile};
};
