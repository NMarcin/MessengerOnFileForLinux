#include <chrono>

#include <Sender.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <FileHandling.hpp>
#include <TerminalFunctionality.hpp>
#include <ChatWindow.hpp>

Sender::Sender(const std::string& pathToChatFile, MessageFlag messageFlag)
    : chatFilenameWithPath_(pathToChatFile),
      messageFlag_(messageFlag)
{
    log.info("Sender C-TOR");
}

Sender::~Sender()
{
    log.info("Sender D-TOR");
}

Message Sender::getMessageToSend() const
{
    log.info("Sender::getMessageToSend started");
    std::string rawMessage = getMessageFromStdin();
    auto messageToSend = prepareMessageToSend(rawMessage);
    return messageToSend;
}

bool Sender::sendMessage(const Message& message) const
{

    bool isMessageSend = FileInterface::Modification::addRow(chatFilenameWithPath_, message.messageToSave());

    if (isMessageSend)
    {
        setNewMessageFlag();
        return true;
    }

    log.info("Sender::sendMessage ERROR: send message fail");
    return false;
}

std::string Sender::getMessageFromStdin() const
{
    log.info("Sender::getMessageFromStdin started");

    std::string message;
    int ch = wgetch(ChatWindow::getEnterMessageWindow());
    while (ch != '\n')
    {
        message.push_back(ch);
        ch = wgetch(ChatWindow::getEnterMessageWindow());
    }

    return message;
}

Message Sender::prepareMessageToSend(const std::string& rowMessage) const
{
    if (isTerminalCommand(rowMessage))
    {
        log.info("Sender::prepearMessageToSend Message is a terminal command");
        TerminalFunctionality terminalFunctionality(chatFilenameWithPath_);
        terminalFunctionality.runCommand(rowMessage);
    }

    return Message(messageFlag_, LocalUser::getLocalUser().getUsername(), rowMessage);
}

bool Sender::isTerminalCommand(const std::string& message) const
{
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
    std::string folderName = *FileInterface::Accesor::getFolderName(chatFilenameWithPath_);
    std::string userRole = std::to_string(static_cast<int>(messageFlag_));
    std::string messageFlagWithPath = folderName + "/NEW_" + userRole;
    bool isNewFlagCreated = FileInterface::Managment::createFile(messageFlagWithPath);
    return isNewFlagCreated;
}

