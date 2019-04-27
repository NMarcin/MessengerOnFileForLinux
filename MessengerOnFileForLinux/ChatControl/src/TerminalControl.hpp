#pragma once

#include <memory>

#include "Logger.hpp"
#include "LogSpace.hpp"
#include "TerminalFunctionality.hpp"
#include "Message.hpp"
#include "SignalHandler.hpp"
#include "NcursesPrintOperationWrapper.hpp"

class TerminalControl
{
public:
    bool waitingInTerminal();
    bool startConversation(const std::string& username, ChatRole chatRole);
    static void lookForInvitation();

    TerminalControl(ChatStatus chatStatus,
                    std::shared_ptr<ChatInformation> chatInfo,
                    const SignalHandler& signalHandler,
                    const NcursesPrintOperationWrapper& informationPrinter);
    ~TerminalControl() = default;

    TerminalControl(TerminalControl &&) = delete;
    TerminalControl operator=(TerminalControl &&) = delete;
    TerminalControl(const TerminalControl &) = delete;
    TerminalControl operator=(const TerminalControl &) = delete;

    static bool isWaitingForInvitation;
    static bool isInvitationExist;

private:
    bool startConversationAsInviter(const std::string& username);
    bool startConversationAsRecipient(const std::string& username);

    std::string _chatFileWithPath;
    std::string _messageFlag;
    ChatStatus _chatStatus;
    std::shared_ptr<ChatInformation> _chatInfo;
    const SignalHandler& _signalHandler;
    const NcursesPrintOperationWrapper& _informationPrinter;
    TerminalFunctionality _terminalFunctionality;

    Logger _log{LogSpace::ChatControl};
};
