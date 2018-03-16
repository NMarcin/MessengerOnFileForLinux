#include <Sender.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <FileHandling.hpp>

Sender::Sender()
{
//NOOP
}

Sender::~Sender()
{
    //NOOP
}

std::unique_ptr<std::string> Sender::enterMessage() const
{
    std::unique_ptr<std::string> message = std::make_unique<std::string>();
    std::cout << "Enter message : ";
    std::cin >> *message;
    return message;
}

bool Sender::sendMessage(const std::string& username) const
{
    std::unique_ptr<std::string> folderName = findChatFolder(username);

    if(nullptr == folderName)
    {
        std::cerr << "If you want to chat with " + username << std::endl;
        std::cerr << "you need to send chat request to him firstly." << std::endl;
        return false;
    }

    std::unique_ptr<std::string> rawMessage = enterMessage();
    std::unique_ptr<std::string> message = prepearMessageToSend(rawMessage);

    FileInterface::addRow("marcin1008_marcin1008", *message, static_cast<std::string>(FILE_::PATH::CHATS_PATH) ); //+ *folderName + "/");

    return true;
}

std::unique_ptr<std::string> Sender::findChatFolder(const std::string& username) const
{
    std::string possibleFolderName_1 = username + "_" + LocalUser::getLocalUser().getUsername();
    std::string possibleFolderName_2 = LocalUser::getLocalUser().getUsername() + "_" + username;
    std::string command_1 = "ls " + static_cast<std::string>(FILE_::PATH::CHATS_PATH) + " | grep " + possibleFolderName_1;
    std::string command_2 = "ls " + static_cast<std::string>(FILE_::PATH::CHATS_PATH) + " | grep " + possibleFolderName_2;

    std::unique_ptr<std::string> folderName = std::make_unique<std::string>(System::getStdoutFromCommand(command_1));

     if (!folderName->empty())
     {
         return folderName;
     }

     folderName = std::make_unique<std::string>(System::getStdoutFromCommand(command_2));

     if (!folderName->empty())
     {
         return folderName;
     }

     return nullptr;
}

std::unique_ptr<std::string> Sender::prepearMessageToSend(const std::string& message) const
{

}

