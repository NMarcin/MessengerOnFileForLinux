#pragma once

#include <Logger.hpp>
#include <LogSpace.hpp>
// nie dodane do kompilowania


enum class MessageFlag
{
    readMessage,
    inviterMessage,
    recipientMessage
};

enum class ChatRole // TO DO mnurzyns usunac jak nie bedzie potrzebne
{
    inviter,
    recipient
};

class TerminalControl //: public ChatControl
{
public:
    bool waitinginTerminal();

private:
    void startConversation(const std::string& username, ChatRole chatRole);
    void startConversationAsInviter(const std::string& username);
    void startConversationAsRecipient(const std::string& username);

    std::string chatFileWithPath_;
    MessageFlag messageFlag_;

    Logger log{LogSpace::ChatFile};
};
