#pragma once
// nie dodane do kompilowania

class TerminalControl //: public ChatControl
{
public:
    void waitinginTerminal();

private:
    void conversationProlog(const std::string& username, ChatRole chatRole);
    void startConversationAsInviter(const std::string& username);
    void startConversationAsRecipient(const std::string& username);
}
