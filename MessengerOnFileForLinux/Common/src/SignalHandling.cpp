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

NcursesPrintToMainWindowOperationWrapper SignalHandler::_nCursesPrintOperationWrapper{};

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
    _nCursesPrintOperationWrapper.printMainWindow();
}

void SignalHandler::terminalResizeHandlerInRegistrationWindow(int)
{
    fileLog("Console resize handled in registration window", LogSpace::Common);
    endwin();
    refresh();
    clear();
    _nCursesPrintOperationWrapper.printRegistrationWindow();
}

void SignalHandler::terminalResizeHandlerInSignInWindow(int)
{
    fileLog("Console resize handled in sign window", LogSpace::Common);
    endwin();
    refresh();
    clear();
    _nCursesPrintOperationWrapper.printSignInWindow();
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
