#include "SignalHandling.hpp"
#include "SignOut.hpp"
#include "ConversationControl.hpp"
#include "FileHandling.hpp"
#include "GlobalVariables.hpp"
#include "ClasslessLogger.hpp"
#include "ConsoleWindow.hpp"
#include "ChatWindow.hpp"

#include <utility>
#include <cstring>

namespace
{
static bool isChatResourcesDealocated = false;

std::string getChatFolderName()
{
    auto fileNamesFormFolder = FileInterface::Accesor::getFilenamesFromFolder(ENVIRONMENT_PATH::TO_FOLDER::CHATS);
    if (fileNamesFormFolder)
    {
        for (const auto& x : *fileNamesFormFolder)
        {
            if (std::string::npos != x.find(getenv("USER")))
            {
                return x;
            }
        }
    }
    return "";
}

void closeMessegner()
{
    SignOut signOut;
    signOut.signOutUser();
    exit (EXIT_SUCCESS);
}
}//namespace

SignalHandler::SignalHandler(const NcursesPrintOperationWrapper& nCursesPrintOperationWrapper)
    : _nCursesPrintOperationWrapper(nCursesPrintOperationWrapper)
{}

void SignalHandler::posixSignalHandlerInMainConsole(int signal)
{
    const std::string log = "Signal nr=" + std::to_string(signal) + "handled in main console";
    fileLog(log.c_str(), LogSpace::Common);
    if (not isChatResourcesDealocated)
    {
        isChatResourcesDealocated = true;
        fileLog("Start of remove chat resources", LogSpace::Common);
        closeMessegner();
    }
}

void SignalHandler::posixSignalHandlerInChatConsole(int signal)
{
    const std::string log = "Signal nr=" + std::to_string(signal) + "handled in chat console";
    fileLog(log.c_str(), LogSpace::Common);

    if (not isChatResourcesDealocated)
    {
        isChatResourcesDealocated = true;
        fileLog("Start of remove chat resources", LogSpace::Common);
        std::string chatFolderName = getChatFolderName();
        if (FileInterface::Managment::isFileExist(ENVIRONMENT_PATH::TO_FOLDER::CHATS + chatFolderName + "/END"))
        {
            std::string command = "rm -rf " + ENVIRONMENT_PATH::TO_FOLDER::CHATS + chatFolderName;
            system(command.c_str());
            closeMessegner();
        }
        else
        {
            FileInterface::Managment::createFile(ENVIRONMENT_PATH::TO_FOLDER::CHATS + chatFolderName + "/END");
            closeMessegner();
        }
    }
}

void SignalHandler::createPosixSignalsHandling(void(*handlingFunction)(int))
{
    for (const auto posixSignal : posixSignalsCausingUnexpectedApplicationEndings)
    {
        std::signal(posixSignal, handlingFunction);
    }
}

void SignalHandler::terminalResizeHandlerInMainWindow(int)
{
    fileLog("Console resize handled in main window", LogSpace::Common);
    endwin();
    refresh();
    clear();
    initscr();
    ConsoleWindow::displayMainWindow();
}

void SignalHandler::terminalResizeHandlerInRegistrationWindow(int)
{
    fileLog("Console resize handled in registration window", LogSpace::Common);
    endwin();
    refresh();
    clear();
    ConsoleWindow::displayRegistrationWindow();
}

void SignalHandler::terminalResizeHandlerInSignInWindow(int)
{
    fileLog("Console resize handled in sign window", LogSpace::Common);
    endwin();
    refresh();
    clear();
    ConsoleWindow::displaySignInWindow();
}

void SignalHandler::terminalResizeHandlerInChatWindow(int)
{
    fileLog("Console resize handled in chat window", LogSpace::Common);
    endwin();
    refresh();
    clear();
    ChatWindow::displayChatWindows();
    ChatWindow::displayEnterMessageWindow();
    ChatWindow::displayDisplayMessageWindow("");
}
/*
namespace SignalHandling
{
void posixSignalHandlerInMainConsole(int signal)
{
    const std::string log = "Signal nr=" + std::to_string(signal) + "handled in main console";
    fileLog(log.c_str(), LogSpace::Common);
    if (not isChatResourcesDealocated)
    {
        isChatResourcesDealocated = true;
        fileLog("Start of remove chat resources", LogSpace::Common);
        closeMessegner();
    }
}

void posixSignalHandlerInChatConsole(int signal)
{
    const std::string log = "Signal nr=" + std::to_string(signal) + "handled in chat console";
    fileLog(log.c_str(), LogSpace::Common);

    if (not isChatResourcesDealocated)
    {
        isChatResourcesDealocated = true;
        fileLog("Start of remove chat resources", LogSpace::Common);
        std::string chatFolderName = getChatFolderName();
        if (FileInterface::Managment::isFileExist(ENVIRONMENT_PATH::TO_FOLDER::CHATS + chatFolderName + "/END"))
        {
            std::string command = "rm -rf " + ENVIRONMENT_PATH::TO_FOLDER::CHATS + chatFolderName;
            system(command.c_str());
            closeMessegner();
        }
        else
        {
            FileInterface::Managment::createFile(ENVIRONMENT_PATH::TO_FOLDER::CHATS + chatFolderName + "/END");
            closeMessegner();
        }
    }
}

void createPosixSignalsHandling(void(*handlingFunction)(int))
{
    for (const auto posixSignal : posixSignalsCausingUnexpectedApplicationEndings)
    {
        std::signal(posixSignal, handlingFunction);
    }
}

namespace NCurses
{
void resizeHandlerInMainWindow(int)
{
    fileLog("Console resize handled in main window", LogSpace::Common);
    endwin();
    refresh();
    clear();
    initscr();
    ConsoleWindow::displayMainWindow();
}

void resizeHandlerInRegistrationWindow(int)
{
    fileLog("Console resize handled in registration window", LogSpace::Common);
    endwin();
    refresh();
    clear();
    ConsoleWindow::displayRegistrationWindow();
}

void resizeHandlerInSignInWindow(int)
{
    fileLog("Console resize handled in sign window", LogSpace::Common);
    endwin();
    refresh();
    clear();
    ConsoleWindow::displaySignInWindow();
}

void resizeHandlerInChatWindow(int)
{
    fileLog("Console resize handled in chat window", LogSpace::Common);
    endwin();
    refresh();
    clear();
    ChatWindow::displayChatWindows();
    ChatWindow::displayEnterMessageWindow();
    ChatWindow::displayDisplayMessageWindow("");
}
}//NCurses
}//SignalHandling
*/
