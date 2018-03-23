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

    std::cout << " JESTEM TU" << std::endl;

    getline(std::cin, *message);

    if (message->empty()) {
        /* ... nothing entered ... */
        std::cout << " NIC NIE PODALISMY" << std::endl;
    }

        return message;

}

bool Sender::sendMessage(const std::string& pathToChatFile, int flag) const
{
    std::cout << " sendMessage" << std::endl;
    std::unique_ptr<std::string> rawMessage = enterMessage();
    std::unique_ptr<std::string> message = prepearMessageToSend(*rawMessage, flag);

    bool isMessageSent = FileInterface::Modification::addRow(pathToChatFile, *message);

    while (!isMessageSent)
    {
        sleep(1);
        isMessageSent = FileInterface::Modification::addRow(pathToChatFile, *message);
    }

    std::unique_ptr<std::string> folderName = FileInterface::Accesor::getFolderName(pathToChatFile);
    bool isFlagSet = setNewMessageFlag(*folderName);

    return isFlagSet;
}

std::unique_ptr<std::string> Sender::prepearMessageToSend(const std::string& rowMessage, int flag) const
{
    std::unique_ptr<std::string> message = std::make_unique<std::string>();
    *message = "[" + std::to_string(flag) + "][" /*DATE&&TIME*/ + LocalUser::getLocalUser().getUsername() + "][" + rowMessage + "]";
    return message;
}

bool Sender::setNewMessageFlag(const std::string& folderName) const
{
    return FileInterface::Managment::createFile(folderName + "/NEW");
}
