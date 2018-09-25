#include <EndConversation.hpp>
#include <ConversationControl.hpp>
#include <FileHandling.hpp>

EndConversation::EndConversation(std::string command, std::shared_ptr<ChatInformation> chatInfo) :
    TerminalCommand(command)
  , chatInfo_(chatInfo)
{

}

EndConversation::~EndConversation()
{

}

bool EndConversation::doCommand()
{
    ConversationControl::isConversationRunning_ = false;
    auto chatFolder = *FileInterface::Accesor::getFolderName(chatInfo_->chatPath_);
    FileInterface::Managment::createFile(chatFolder + "/END_" + chatInfo_->messageFlag_);
}
