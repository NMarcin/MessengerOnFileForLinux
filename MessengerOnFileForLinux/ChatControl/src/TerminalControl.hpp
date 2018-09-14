#pragma once

#include <Logger.hpp>
#include <LogSpace.hpp>
#include <TerminalFunctionality.hpp>
#include <memory>
#include <Message.hpp>
// nie dodane do kompilowania


class TerminalControl //: public ChatControl
{
public:
    bool waitingInTerminal();
    void startConversation(const std::string& username, std::string chatRole); // TO DO mwozniak to private, but temporary is here because GlobalVariables.hpp

private:
    void startConversationAsInviter(const std::string& username);
    void startConversationAsRecipient(const std::string& username);

    std::string chatFileWithPath_;
    std::string messageFlag_;
    TerminalFunctionality terminalFunctionality_;

    Logger log{LogSpace::ChatFile};
};
