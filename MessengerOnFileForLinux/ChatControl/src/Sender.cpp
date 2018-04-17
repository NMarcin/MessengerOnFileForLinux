#include <chrono>

#include <Sender.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <FileHandling.hpp>


Sender::Sender(const std::string& pathToChatFile, int chatFlag)
    : chatFilenameWithPath_(pathToChatFile),
      chatFlag_(chatFlag)
{
    log.info("Sender C-TOR");
}

Sender::~Sender()
{
    log.info("Sender D-TOR");
}

std::unique_ptr<std::string> Sender::getMessageToSend() const
{
    log.info("Sender::getMessageToSend started");
    std::unique_ptr<std::string> rawMessage = getMessageFromStdin();
    std::unique_ptr<std::string> messageToSend = prepareMessageToSend(*rawMessage);
    return messageToSend;
}

bool Sender::sendMessage(const std::string& message) const
{
    log.info("Sender::sendMessage started");
    bool isMessageSend = FileInterface::Modification::addRow(chatFilenameWithPath_, message);

    if (isMessageSend)
    {
        setNewMessageFlag();
        return true;
    }

    return false;
}

std::unique_ptr<std::string> Sender::getMessageFromStdin() const
{
    log.info("Sender::getMessageFromStdin started");
    std::unique_ptr<std::string> message = std::make_unique<std::string>();
    std::cin >> std::ws;
    getline(std::cin, *message);
    return message;
}

std::unique_ptr<std::string> Sender::prepareMessageToSend(const std::string& rowMessage) const
{
    log.info("Sender::prepearMessageToSend started");
    std::unique_ptr<std::string> message = std::make_unique<std::string>();
    *message = "[" + std::to_string(chatFlag_) + "][" + *getActualDateTime() + "][" + LocalUser::getLocalUser().getUsername() + "][" + rowMessage + "]";
    return message;
}

bool Sender::setNewMessageFlag() const
{
    log.info("Sender::setNewMessageFlag started");
    std::string folderName = *FileInterface::Accesor::getFolderName(chatFilenameWithPath_);
    bool isNewFlagCreated = FileInterface::Managment::createFile(folderName + "/NEW");
    return isNewFlagCreated;
}

std::unique_ptr<std::string> Sender::getActualDateTime() const
{
    log.info("Sender::getActualDateTime started");
    std::unique_ptr<std::string> dateTime = std::make_unique<std::string>();
    *dateTime = __DATE__;
    *dateTime += " | " ;
    *dateTime += __TIME__;
    return dateTime;
}
