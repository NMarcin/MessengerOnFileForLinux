#include"TerminalControl.hpp"
#include "ChatRequest.hpp"
#include "ConversationControl.hpp"
#include "GlobalVariables.hpp"
#include "ConsoleWindow.hpp"
#include "FileHandling.hpp"

#include <iostream>
#include <memory>
#include <csignal>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <streambuf>
#include <sstream>


TerminalControl::TerminalControl(ChatStatus chatStatus,
                                 std::shared_ptr<ChatInformation> chatInfo,
                                 const SignalHandler& signalHandler,
                                 const NcursesPrintOperationWrapper& informationPrinter)
                                : _chatStatus(chatStatus)
                                , _chatInfo(chatInfo)
                                , _signalHandler(signalHandler)
                                , _informationPrinter(informationPrinter)
                                , _terminalFunctionality(_signalHandler, _informationPrinter)
{
    // NOOP
}

bool TerminalControl::isWaitingForInvitation = true;
bool TerminalControl::isInvitationExist = false;

bool TerminalControl::waitingInTerminal()
{
    _log.function("TerminalControl::waitingInTerminal() started");
    std::signal(SIGWINCH, _signalHandler.terminalResizeHandlerInMainWindow);
    clear();
    refresh();
    _informationPrinter.printMainWindow();
    const std::string command = ConsoleWindow::getStringFromConsoleWindow();
    bool commandStatus = _terminalFunctionality.runCommand(command, _chatInfo);
    return commandStatus;
}

bool TerminalControl::startConversation(const std::string& username, ChatRole chatRole)
{
    _log.function(("ChatControl::startConversation() started whit chatRole = " + std::to_string(static_cast<int>(chatRole))).c_str());
    if (ChatRole::inviter == chatRole)
    {
        return startConversationAsInviter(username);
    }
    else if (ChatRole::recipient == chatRole)
    {
        return startConversationAsRecipient(username);
    }
    return false;
}

bool TerminalControl::startConversationAsInviter(const std::string& username)
{
    _log.function("TerminalControl::startConversationAsInviter() started");
    ChatRequest chatRequest;
    _chatFileWithPath = chatRequest.sendChatRequest(username);
    if(!_chatFileWithPath.empty())
    {
        _chatInfo->_chatPath = _chatFileWithPath;
        _chatInfo->_messageFlag = MessageFlag::inviterMessage;
        _chatInfo->_interlocutorUsername = username;
        return true;
    }
    return false;
}

bool TerminalControl::startConversationAsRecipient(const std::string& username)
{
    _log.function("TerminalControl::startConversationAsRecipient() started");
    ChatRequest chatRequest;
    _chatFileWithPath = chatRequest.answerForChatRequest(username, "accept");
    if(!_chatFileWithPath.empty())
    {
        _chatInfo->_chatPath = _chatFileWithPath;
        _chatInfo->_messageFlag = MessageFlag::recipientMessage;
        _chatInfo->_interlocutorUsername = username;
        return true;
    }
    return false;
}


void TerminalControl::lookForInvitation()
{
    while (isWaitingForInvitation)
    {
        auto invitationsFolderContent = FileInterface::Accesor::getFilenamesFromFolder(ENVIRONMENT_PATH::TO_FOLDER::INVITATIONS);
        if (0 == invitationsFolderContent->size())
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }
        for(auto invitation : *invitationsFolderContent)
        {
            std::string recipent;
            std::string inviter;
            bool getRecipentName = true;

            for (auto letter : invitation)
            {
                if (!getRecipentName)
                {
                    inviter += letter;
                }

                else if ('_' != letter)
                {
                    recipent += letter;
                }

                else if ( '_' == letter)
                {
                    getRecipentName = false;
                }

            }

            if (recipent == getenv("USER"))
            {
                isInvitationExist = true;
                clear();
                printw(("You get an invitation to chat form " + inviter + "\n").c_str());
                printw(("Do you want to chat with this user (start " + inviter + "/n)? \n").c_str());
                printw(">> ");
                refresh();
                isWaitingForInvitation=false;
                std::string invitationName =  LOCAL_USER + "_" + inviter;
                FileInterface::Managment::removeFile(ENVIRONMENT_PATH::TO_FOLDER::INVITATIONS + invitationName);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

    }
}
