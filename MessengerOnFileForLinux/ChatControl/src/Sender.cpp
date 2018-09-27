#include <chrono>

#include <Sender.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <FileHandling.hpp>
#include <TerminalFunctionality.hpp>
#include <ChatWindow.hpp>
#include <ConversationControl.hpp>

Sender::Sender(std::shared_ptr<ChatInformation> chatInfo)
    : chatInfo_(chatInfo)
{
    log.info("Sender C-TOR");
}

Sender::~Sender()
{
    log.function("Sender D-TOR");
}

std::unique_ptr<Message> Sender::getMessageToSend() const
{
    log.function("Sender::getMessageToSend() started");
    std::string rawMessage = getMessageFromStdin();
    auto messageToSend = prepareMessageToSend(rawMessage);
    return std::move(messageToSend);
}

bool Sender::sendMessage(const Message& message) const
{
    log.function("Sender::sendMessage() started");

    bool isMessageSend = FileInterface::Modification::addRow(chatInfo_->chatPath_, message.messageToSave());
    if (isMessageSend)
    {
        setNewMessageFlag();
        auto sentMessage = message.messageToSave();
        log.debug("Sender::sendMessage() success. Sent message = ");
        log.debug(sentMessage);
        return true;
    }

    log.info("Sender::sendMessage WARNING: send message fail");
    return false;
}

std::string Sender::getMessageFromStdin() const
{
    log.function("Sender::getMessageFromStdin() started");
    std::string message;

    int ch = wgetch(ChatWindow::getEnterMessageWindow());
    while (ch != '\n')
    {
        message.push_back(ch);
        ch = wgetch(ChatWindow::getEnterMessageWindow());
    }

    return message;
}

std::unique_ptr<Message> Sender::prepareMessageToSend(const std::string& rowMessage) const
{
    log.function("Sender::prepareMessageToSend() started");
    if (isTerminalCommand(rowMessage))
    {
        log.info("Sender::prepearMessageToSend() Message is a conversation command");
        TerminalFunctionality terminalFunctionality(chatInfo_->chatPath_, ChatStatus::conversation);
        std::string command = std::string{rowMessage.begin()+2, rowMessage.end()};
        terminalFunctionality.runCommand(command, chatInfo_);
        if("end" == command)
        {
            std::string systemMessage = LocalUser::getLocalUser().getUsername() + " LEFT CHAT";
            return std::make_unique<Message>(chatInfo_->messageFlag_, "SYSTEM" ,systemMessage);
        }
        return nullptr;
    }

    return std::make_unique<Message>(chatInfo_->messageFlag_, LocalUser::getLocalUser().getUsername(), rowMessage);
}

bool Sender::isTerminalCommand(const std::string& message) const
{
    log.function("Sender::isTerminalCommand() started");
    if (2 > message.size())
    {
        return false;
    }
    if ("//" == std::string(message.begin(), message.begin()+2))
    {
        return true;
    }

    return false;
}

bool Sender::setNewMessageFlag() const
{
    log.function("Sender::setNewMessageFlag() started");
    std::string folderName = *FileInterface::Accesor::getFolderName(chatInfo_->chatPath_);
    std::string messageFlagWithPath = folderName + "/NEW_" + chatInfo_->messageFlag_;
    bool isNewFlagCreated = FileInterface::Managment::createFile(messageFlagWithPath);
    return isNewFlagCreated;
}
