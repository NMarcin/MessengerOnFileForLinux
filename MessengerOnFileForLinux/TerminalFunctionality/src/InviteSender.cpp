#include "InviteSender.hpp"
#include "TerminalControl.hpp"
#include "ConversationControl.hpp"


InviteSender::InviteSender(std::string command,
                           std::shared_ptr<ChatInformation> chatInfo,
                           const SignalHandler& signalHandler,
                           const NcursesPrintOperationWrapper& informationPrinter)
    : TerminalCommand(command)
    , _signalHandler(signalHandler)
    , _informationPrinter(informationPrinter)
{
    _log.function("InviteSender() C-TOR");
}

InviteSender::~InviteSender()
{
    _log.function("InviteSender() D-TOR");
}

bool InviteSender::doCommand() const
{
    _log.function("InviteSender()::doCommand() started");

    std::string usernameInCommand = std::string{_command.begin()+7, _command.end()};
    std::string logInfo = "Invite send to: " + usernameInCommand;
    _log.info(logInfo);

    TerminalControl terminalControl(ChatStatus::terminal, _chatInfo, _signalHandler, _informationPrinter);
    return terminalControl.startConversation(usernameInCommand, ChatRole::inviter);
}
