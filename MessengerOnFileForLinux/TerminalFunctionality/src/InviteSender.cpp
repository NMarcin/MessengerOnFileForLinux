#include <InviteSender.hpp>
#include <TerminalControl.hpp>

#include <ConversationControl.hpp>

InviteSender::InviteSender(std::string command) : TerminalCommand(command)
{

}

InviteSender::~InviteSender()
{

}

bool InviteSender::doCommand(TerminalControl *x)
{

    auto beginOfUsernameInCommand = command_.begin()+7;
    std::string username = {beginOfUsernameInCommand, command_.end()};
    TerminalControl terminalControl;
    x->startConversation(username, ChatRole::inviter);
}
