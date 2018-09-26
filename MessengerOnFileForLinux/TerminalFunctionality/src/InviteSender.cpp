#include <InviteSender.hpp>
#include <TerminalControl.hpp>

#include <ConversationControl.hpp>

InviteSender::InviteSender(std::string command, std::shared_ptr<ChatInformation> chatInfo) :
    TerminalCommand(command)
  , command_(command)
  , chatInfo_(chatInfo)
{
    log_.function("InviteSender() C-TOR");
}

InviteSender::~InviteSender()
{
    log_.function("InviteSender() D-TOR");
}

bool InviteSender::doCommand()
{
    log_.function("InviteSender()::doCommand() started");

    std::string usernameInCommand = std::string{command_.begin()+7, command_.end()};
    std::string logInfo = "Invite send to: " + usernameInCommand;
    log_.info(logInfo);

    TerminalControl terminalControl(ChatStatus::terminal, chatInfo_);
    return terminalControl.startConversation(usernameInCommand, ChatRole::inviter);
}
