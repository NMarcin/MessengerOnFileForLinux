#pragma once

#include <Logger.hpp>
#include <LogSpace.hpp>
#include <ChatData.hpp>
#include <memory>
// nie dodane do kompilowania


class TerminalControl //: public ChatControl
{
public:
    bool waitingInTerminal();
    void startConversation(const std::string& username, ChatRole chatRole); // TO DO mwozniak to private, but temporary is here because GlobalVariables.hpp
    std::shared_ptr<ChatData> getChatData();

private:
    void startConversationAsInviter(const std::string& username);
    void startConversationAsRecipient(const std::string& username);

    std::string chatFileWithPath_;
    MessageFlag messageFlag_;
    std::shared_ptr<ChatData> chatData_;

    Logger log{LogSpace::ChatFile};
};
