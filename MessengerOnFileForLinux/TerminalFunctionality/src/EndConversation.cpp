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
    log_.function("EndConversation::doCommand() start");
    ConversationControl::isConversationRunning_ = false;

    auto chatFolder = *FileInterface::Accesor::getFolderName(chatInfo_->chatPath_);
    if (FileInterface::Managment::isFileExist(chatFolder + "/END"))
    {
        log_.info("EndConversation::doCommand() remove chat folder");
        log_.info(chatFolder);
        std::string command = "rm -rf " + chatFolder;
        return system(command.c_str());
    }
    return FileInterface::Managment::createFile(chatFolder + "/END");
}
