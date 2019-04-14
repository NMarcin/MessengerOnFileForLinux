#include <chrono>

#include "Sender.hpp"
#include "GlobalVariables.hpp"
#include "FileHandling.hpp"
#include "TerminalFunctionality.hpp"
#include "ChatWindow.hpp"
#include "ConversationControl.hpp"

Sender::Sender(std::shared_ptr<ChatInformation> chatInfo)
    : _chatInfo(chatInfo)
{
    _log.info("Sender C-TOR");
}

std::unique_ptr<Message> Sender::getMessageToSend() const
{
    _log.function("Sender::getMessageToSend() started");
    std::string rawMessage = getMessageFromStdin();
    auto messageToSend = prepareMessageToSend(rawMessage);
    return messageToSend;
}

bool Sender::sendMessage(const Message& message) const
{
    _log.function("Sender::sendMessage() started");

    bool isMessageSend = FileInterface::Modification::addRow(_chatInfo->_chatPath, message.messageToSave());
    if (isMessageSend)
    {
        setNewMessageFlag();
        auto sentMessage = message.messageToSave();
        _log.debug("Sender::sendMessage() success. Sent message = ");
        _log.debug(sentMessage);
        return true;
    }

    _log.info("Sender::sendMessage WARNING: send message fail");
    return false;
}

std::string Sender::getMessageFromStdin() const
{
    _log.function("Sender::getMessageFromStdin() started");
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
    _log.function("Sender::prepareMessageToSend() started");
    if (isTerminalCommand(rowMessage))
    {
        _log.info("Sender::prepearMessageToSend() Message is a conversation command");
        TerminalFunctionality terminalFunctionality(_chatInfo->_chatPath, ChatStatus::conversation);
        std::string command = std::string{rowMessage.begin()+2, rowMessage.end()};
        terminalFunctionality.runCommand(command, _chatInfo);
        if("end" == command)
        {
            std::string systemMessage = LOCAL_USER + " LEFT CHAT";
            return std::make_unique<Message>(_chatInfo->_messageFlag, "_SYSTEM_" ,systemMessage);
        }
        return nullptr;
    }

    return std::make_unique<Message>(_chatInfo->_messageFlag, LOCAL_USER, rowMessage);
}

bool Sender::isTerminalCommand(const std::string& message) const
{
    _log.function("Sender::isTerminalCommand() started");
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
    _log.function("Sender::setNewMessageFlag() started");
    std::string folderName = *FileInterface::Accesor::getFolderName(_chatInfo->_chatPath);
    std::string messageFlagWithPath = folderName + "/NEW_" + _chatInfo->_messageFlag;
    bool isNewFlagCreated = FileInterface::Managment::createFile(messageFlagWithPath);
    return isNewFlagCreated;
}
