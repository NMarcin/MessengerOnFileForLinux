#include "InviteReceiver.hpp"
#include "TerminalControl.hpp"
#include "ConversationControl.hpp"

InviteReceiver::InviteReceiver(std::string command,
                               std::shared_ptr<ChatInformation> chatInfo,
                               const SignalHandler& signalHandler,
                               const NcursesPrintOperationWrapper& informationPrinter)
    : TerminalCommand(command)
    , _chatInfo(chatInfo)
    , _signalHandler(signalHandler)
    , _informationPrinter(informationPrinter)
{
    _log.function("InviteReceiver() C-TOR");
}

bool InviteReceiver::doCommand() const
{
    _log.function("InviteReceiver()::doCommand() started");
    if (TerminalControl::isInvitationExist)
    {
        std::string usernameInCommand = std::string{_command.begin()+6, _command.end()};
        TerminalControl terminalControl(ChatStatus::terminal, _chatInfo, _signalHandler, _informationPrinter);
        return terminalControl.startConversation(usernameInCommand, ChatRole::recipient);
    }
    _log.info("InviteReceiver()::doCommand() WARNING: Try to start conversation without invitation");
    return false;
}
