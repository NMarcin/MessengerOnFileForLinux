#include <chrono>
#include <thread>
#include <stdio.h>

#include "ConversationControl.hpp"
#include "FileHandling.hpp"
#include "ChatRequest.hpp"
#include "GlobalVariables.hpp"
#include "ChatWindow.hpp"
#include "ConsoleWindow.hpp"
#include "PurgeMessage.hpp"

bool ConversationControl::isConversationRunning_ = false;

ConversationControl::ConversationControl(std::shared_ptr<ChatInformation> chatInfo,
                                         const SignalHandler& signalHandler,
                                         const NcursesPrintOperationWrapper& informationPrinter)
    : _chatInfo(chatInfo)
    , _sender(std::make_unique<Sender>(chatInfo))
    , _receiver(std::make_unique<Receiver>(chatInfo))
    , _getMessageToQueueThread(nullptr)
    , _sendMessageFromQueueThread(nullptr)
    , _reciveMessageThread(nullptr)
    , _isUserInactivityWasHandled(false)
    , _userInactivityDetector(chatInfo->_interlocutorUsername)
    , _signalHandler(signalHandler)
    , _informationPrinter(informationPrinter)
{
    _log.function("ChatControl C-TOR ");
    isConversationRunning_ = true;
}

ConversationControl::~ConversationControl()
{
    _log.function("ChatControl D-TOR ");

    if (_getMessageToQueueThread && _reciveMessageThread)
    {
        _getMessageToQueueThread->join();
        _reciveMessageThread->join();
        _sendMessageFromQueueThread->join();
    }
}

void ConversationControl::conversation()
{
    _log.function("ChatControl::conversationControl() started");
    _signalHandler.createPosixSignalsHandling(_signalHandler.posixSignalHandlerInChatConsole);
    ChatWindow::displayChatWindows();
    startThreads();
    while (isConversationRunning_)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void ConversationControl::conversationEpilog()
{
    _log.function("ChatControl::endConversation() started");
    stopThreads();

    ChatWindow::deleteDisplayMesageWindow();
    ChatWindow::deleteEnterMesageWindow();
    _informationPrinter.printMainWindow();

    const std::string userActiveStatus = "0";
    const std::string username = LOCAL_USER;
    FileInterface::Modification::updateRowField(ENVIRONMENT_PATH::TO_FILE::LOGGED, username, userActiveStatus, FileStructure::LoggedFile::status);
}

void ConversationControl::getMessage()
{
    _log.function("ChatControl::getMessage() started");

    while(_isThreadsRunning)
    {
        ChatWindow::displayEnterMessageWindow();
        if (isConversationRunning_)
        {
            auto message = _sender->getMessageToSend();
            if(message)
            {
                _messageReadyToSend.push(*message);
            }
            else
            {
                continue;
            }

            PurgeMessage ownMessageToDisplay(_messageReadyToSend.front());
            _messageToDisplay.push(ownMessageToDisplay);
        }
        _log.debug("ChatControl::getMessage() isConversationRunning_ = false");
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

bool ConversationControl::isMessagesToReadExist()
{
    auto chatFolder = *FileInterface::Accesor::getFolderName(_chatInfo->_chatPath);

    if(MessageFlag::inviterMessage == _chatInfo->_messageFlag)
    {
        return FileInterface::Managment::isFileExist(chatFolder + "/NEW_" + MessageFlag::recipientMessage);
    }
    else if(MessageFlag::recipientMessage == _chatInfo->_messageFlag)
    {
        return FileInterface::Managment::isFileExist(chatFolder + "/NEW_" + MessageFlag::inviterMessage);
    }
    return false;
}

void ConversationControl::handleInterlocutorInactivity()
{
    if(not _isUserInactivityWasHandled)
    {
        markUserInactivityAsHandled();
        const std::string pathToChatFolder = *FileInterface::Accesor::getFolderName(_chatInfo->_chatPath);
        const std::string systemMessage = "Your interlocutor is inactive! You can leve chat";
        Message message(_chatInfo->_messageFlag, "_SYSTEM_", systemMessage);
        _sender->sendMessage(message);
        _messageToDisplay.push(message);
        FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, _chatInfo->_interlocutorUsername);
        FileInterface::Managment::createFile(pathToChatFolder + "/END");
    }
}

void ConversationControl::markUserInactivityAsHandled()
{
    _isUserInactivityWasHandled = true;
}

void ConversationControl::reciveMessage()
{
    _log.function("ChatControl::reciveMessage() started");

    while(_isThreadsRunning)
    {
        _userInactivityDetector.detectUserInactivity();

        if (!_messageToDisplay.empty())
        {
            ChatWindow::displayDisplayMessageWindow(_messageToDisplay.front().messageToShow() + "\n");
            _messageToDisplay.pop();
        }
        else if (_userInactivityDetector.isUserInactiveDetected())
        {
            handleInterlocutorInactivity();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        if (isMessagesToReadExist())
        {
            _receiver->readMessagesToStack();
            saveMessageToDisplay();
        }
    }
}

void ConversationControl::sendMessage()
{
    _log.function("ChatControl::sendMessage() started");
    while(_isThreadsRunning || !_messageReadyToSend.empty())
    {
        if (_messageReadyToSend.empty())
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else
        {
            _sender->sendMessage(_messageReadyToSend.front());
            _messageReadyToSend.pop();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void ConversationControl::startThreads()
{
    _log.function("ChatControl::startThreads() started");
    _isThreadsRunning = true;

    _getMessageToQueueThread = std::make_unique<std::thread>(std::thread([&]()
    {
        getMessage();
    }));

    _reciveMessageThread = std::make_unique<std::thread>(std::thread([&]()
    {
        reciveMessage();
    }));

    _sendMessageFromQueueThread = std::make_unique<std::thread>(std::thread([&]()
    {
        sendMessage();
    }));
}

void ConversationControl::saveMessageToDisplay()
{
    _log.function("ChatControl::saveMessageToDisplay() started");
    bool isEndOfMessages = false;
    while(!isEndOfMessages)
    {
        auto message = _receiver->returnTheOldestMessage();
        if(nullptr == message)
        {
            isEndOfMessages = true;
        }
        else
        {
            _messageToDisplay.push(*message);
        }
    }
}

void ConversationControl::stopThreads()
{
    _log.function("ChatControl::stopThreads() started");
    _isThreadsRunning = false;
}
