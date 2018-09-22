#include<TerminalControl.hpp>

#include <ChatRequest.hpp>
#include <ConversationControl.hpp>
#include <GlobalVariables.hpp>

#include <iostream>
// REMEMBER TO ADD THIS FILE INTO TEST CMAKELISTS

TerminalControl::TerminalControl(ChatStatus chatStatus)
                                : chatStatus_(chatStatus)
{
    // NOOP
}

bool TerminalControl::waitingInTerminal()
{
    log_.function("TerminalControl::waitingInTerminal()");
    std::string command;
    std::cin >> command;
    bool commandStatus;
    commandStatus = terminalFunctionality_.runCommand(command);

    return commandStatus;
}

void TerminalControl::startConversation(const std::string& username, ChatRole chatRole)
{
    log_.function(("ChatControl::startConversation started whit chatRole = " + std::to_string(static_cast<int>(chatRole))).c_str());
    if (ChatRole::inviter == chatRole)
    {
        startConversationAsInviter(username);
    }
    else if (ChatRole::recipient == chatRole)
    {
        startConversationAsRecipient(username);
    }
}

void TerminalControl::startConversationAsInviter(const std::string& username)
{
    log_.function("TerminalControl::startConversationAsInviter()");
    ChatRequest chatRequest;
    chatFileWithPath_ = chatRequest.sendChatRequest(username);
    if(!chatFileWithPath_.empty())
    {
        std::string info = "ChatControl::startConversationAsInviter chatFileWithPath_: " + chatFileWithPath_;
        log_.info(info.c_str());
        messageFlag_ = MessageFlag::inviterMessage;
        ConversationControl conversation(chatFileWithPath_, messageFlag_);
        conversation.conversation();
    }
}

void TerminalControl::startConversationAsRecipient(const std::string& username)
{
    log_.function("TerminalControl::startConversationAsRecipient()");
    ChatRequest chatRequest;
    chatFileWithPath_ = chatRequest.answerForChatRequest(username);
    if(!chatFileWithPath_.empty())
    {
        std::string info = "ChatControl::startConversationAsRecipient chatFileWithPath_: " + chatFileWithPath_;
        log_.info(info.c_str());
        messageFlag_ = MessageFlag::recipientMessage;
        ConversationControl conversation(chatFileWithPath_, messageFlag_);
        conversation.conversation();
    }
}
