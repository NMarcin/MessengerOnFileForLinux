#include <InviteReceiver.hpp>
#include <TerminalControl.hpp>

#include <ConversationControl.hpp>

InviteReceiver::InviteReceiver(std::string command, std::shared_ptr<ChatInformation> chatInfo) :
    TerminalCommand(command)
  , command_(command)
  , chatInfo_(chatInfo)
{
    log_.function("InviteReceiver() C-TOR");
}

InviteReceiver::~InviteReceiver()
{
    log_.function("InviteReceiver() D-TOR");
}

bool InviteReceiver::doCommand()
{
    log_.function("InviteReceiver()::doCommand() started");
    if (TerminalControl::isInvitationExist)
    {
        std::string usernameInCommand = std::string{command_.begin()+6, command_.end()};
        TerminalControl terminalControl(ChatStatus::terminal, chatInfo_);
        return terminalControl.startConversation(usernameInCommand, ChatRole::recipient);
    }
    log_.info("InviteReceiver()::doCommand() WARNING: Try to start conversation without invitation");
    return false;
}
