#include <EndConversation.hpp>
#include <ConversationControl.hpp>

#include <ConversationControl.hpp>

EndConversation::EndConversation(std::string command) : TerminalCommand(command)
{

}

EndConversation::~EndConversation()
{
    ConversationControl::isConversationRunning_ = false;
}

bool EndConversation::doCommand()
{

}
