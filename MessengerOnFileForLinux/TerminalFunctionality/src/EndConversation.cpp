#include <EndConversation.hpp>
#include <ConversationControl.hpp>
#include <FileHandling.hpp>

EndConversation::EndConversation(std::string command, std::shared_ptr<ChatInformation> chatInfo) :
    TerminalCommand(command)
  , _chatInfo(chatInfo)
{
    _log.function("EndConversation() C-TOR");
}

bool EndConversation::doCommand()
{
    _log.function("EndConversation::doCommand() start");

    ConversationControl::isConversationRunning_ = false;
    auto chatFolder = *FileInterface::Accesor::getFolderName(_chatInfo->_chatPath);

    if (FileInterface::Managment::isFileExist(chatFolder + "/END"))
    {
        _log.info("EndConversation::doCommand() remove chat folder");
        _log.info(chatFolder);
        std::string command = "rm -rf " + chatFolder;
        return system(command.c_str());
    }

    _log.info("EndConversation::doCommand() create END flag");
    return FileInterface::Managment::createFile(chatFolder + "/END");
}
