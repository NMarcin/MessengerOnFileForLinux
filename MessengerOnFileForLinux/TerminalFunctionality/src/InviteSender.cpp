#include <InviteSender.hpp>
#include <TerminalControl.hpp>

#include <ConversationControl.hpp>

InviteSender::InviteSender(std::string command, std::shared_ptr<ChatInformation> chatInfo) :
    TerminalCommand(command)
  , command_(command)
  , chatInfo_(chatInfo)
{
    log_.info("InviteSender() CTOR");
    int x = command.size();
    log_.info(std::to_string(x).c_str());
}

InviteSender::~InviteSender()
{

}

bool InviteSender::doCommand()
{
    log_.info("InviteSender()::doCommand()");
    std::string usernameInCommand = std::string{command_.begin()+7, command_.end()};
    TerminalControl terminalControl(ChatStatus::terminal, chatInfo_);
    terminalControl.startConversation(usernameInCommand, ChatRole::inviter);
}
