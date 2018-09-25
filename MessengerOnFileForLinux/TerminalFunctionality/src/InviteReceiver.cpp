#include <InviteReceiver.hpp>
#include <TerminalControl.hpp>

#include <ConversationControl.hpp>

InviteReceiver::InviteReceiver(std::string command, std::shared_ptr<ChatInformation> chatInfo) :
    TerminalCommand(command)
  , command_(command)
  , chatInfo_(chatInfo)
{
    log_.info("InviteSender() CTOR");
}

InviteReceiver::~InviteReceiver()
{

}

bool InviteReceiver::doCommand()
{
    log_.info("InviteSender()::doCommand()");
    if (TerminalControl::isInvitationExist)
    {
        std::string usernameInCommand = std::string{command_.begin()+6, command_.end()};
        TerminalControl terminalControl(ChatStatus::terminal, chatInfo_);
        return terminalControl.startConversation(usernameInCommand, ChatRole::recipient);
    }
    return false;
}
