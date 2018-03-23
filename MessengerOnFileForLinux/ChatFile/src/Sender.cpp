#include <chrono>

#include <Sender.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <FileHandling.hpp>


Sender::Sender(const std::string& pathToChatFile, int chatFlag)
    : pathToChatFile_(pathToChatFile),
      chatFlag_(chatFlag)
{
    //NOOP
}

Sender::~Sender()
{
    while (!messageWaitngRoom_.empty())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    isMessageWaitngRoomEmpty_ = true;
    trySendMessage_.join();
}

std::unique_ptr<std::string> Sender::getMessageFromStdin() const
{
    std::unique_ptr<std::string> message = std::make_unique<std::string>();
    std::cin >> std::ws;
    getline(std::cin, *message);
    return message;
}

bool Sender::sendMessage()
{
    std::unique_ptr<std::string> rawMessage = getMessageFromStdin();
    bool isMessagePreapeared = prepearMessageToSend(*rawMessage);

    return isMessagePreapeared;
}

bool Sender::prepearMessageToSend(const std::string& rowMessage)
{
    std::unique_ptr<std::string> message = std::make_unique<std::string>();
    *message = "[" + std::to_string(chatFlag_) + "][" + *getActualDateTime() + "][" + LocalUser::getLocalUser().getUsername() + "][" + rowMessage + "]";
    messageWaitngRoom_.push(std::move(message));
    return true;
}

bool Sender::setNewMessageFlag(const std::string& folderName) const
{
    return FileInterface::Managment::createFile(folderName + "/NEW");
}

std::unique_ptr<std::string> Sender::getActualDateTime() const
{
    std::unique_ptr<std::string> dateTime = std::make_unique<std::string>();
    *dateTime = __DATE__;
    *dateTime += " | " ;
    *dateTime += __TIME__;
    return dateTime;
}

void Sender::trySendMessage()
{
    while (!isMessageWaitngRoomEmpty_)
    {
        if (messageWaitngRoom_.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        else
        {
            std::unique_ptr<std::string> messageToSend = std::move(messageWaitngRoom_.front());
            bool isMessageSent = FileInterface::Modification::addRow(pathToChatFile_, *messageToSend);

            if (isMessageSent)
            {
                std::unique_ptr<std::string> folderName = FileInterface::Accesor::getFolderName(pathToChatFile_);
                setNewMessageFlag(*folderName);
                messageWaitngRoom_.pop();
            }
        }
    }
}

