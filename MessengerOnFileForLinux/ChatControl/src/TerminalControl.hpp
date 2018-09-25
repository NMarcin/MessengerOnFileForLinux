#pragma once

#include <Logger.hpp>
#include <LogSpace.hpp>
#include <TerminalFunctionality.hpp>
#include <memory>
#include <Message.hpp>


class TerminalControl : public std::enable_shared_from_this<TerminalControl>
{
public:
    bool waitingInTerminal();
    bool startConversation(const std::string& username, ChatRole chatRole);
    static void lookForInvitation();
    TerminalControl(ChatStatus chatStatus, std::shared_ptr<ChatInformation> chatInfo);
    TerminalControl(ChatStatus chatStatus);
    ~TerminalControl() = default;
    static bool isWaitingForInvitation;

private:
    bool startConversationAsInviter(const std::string& username);
    bool startConversationAsRecipient(const std::string& username);




    std::string chatFileWithPath_;
    std::string messageFlag_;
    TerminalFunctionality terminalFunctionality_;
    ChatStatus chatStatus_;
    std::shared_ptr<ChatInformation> chatInfo_;



    Logger log_{LogSpace::ChatControl};
};
