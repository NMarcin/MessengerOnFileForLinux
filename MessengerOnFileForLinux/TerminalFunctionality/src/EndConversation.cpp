#include <EndConversation.hpp>
#include <ConversationControl.hpp>

#include <ConversationControl.hpp>

EndConversation::EndConversation(std::string command) : TerminalCommand(command)
{

}

EndConversation::~EndConversation()
{

}

bool EndConversation::doCommand()
{
    ConversationControl::isConversationRunning_ = false;
}
