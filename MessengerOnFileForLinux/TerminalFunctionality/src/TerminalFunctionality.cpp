#include "TerminalFunctionality.hpp"
#include "UserCommand.hpp"
#include "HistoryDowloander.hpp"
#include "LoggingOut.hpp"
#include "InviteSender.hpp"
#include "GlobalVariables.hpp"
#include "EndConversation.hpp"
#include "InviteReceiver.hpp"
#include "ConsoleWindow.hpp"

namespace
{
bool starts_with(const std::string& starter, const std::string& ourString);
} // namespace

TerminalFunctionality::TerminalFunctionality(std::string chatFileWithPath,
                                             ChatStatus chatStatus,
                                             const SignalHandler& signalHandler,
                                             const NcursesPrintOperationWrapper& informationPrinter)
    : _chatFileWithPath(chatFileWithPath)
    , _chatStatus(chatStatus)
    , _signalHandler(signalHandler)
    , _informationPrinter(informationPrinter)
{
    //NOOP
}

TerminalFunctionality::TerminalFunctionality(const SignalHandler& signalHandler,
                                             const NcursesPrintOperationWrapper& informationPrinter)

    : _signalHandler(signalHandler)
    , _informationPrinter(informationPrinter)
{}

bool TerminalFunctionality::runCommand(const std::string& command, std::shared_ptr<ChatInformation> chatInfo)
{
    _log.function("TerminalFunctionality::runCommand() started");

    if (starts_with(UserCommand::historyDowloander, command) && ChatStatus::conversation == _chatStatus)
    {
        _log.info("TerminalFunctionality::runCommand() historyDowloander command");
        _terminalCommand = std::make_unique<HistoryDowloander>(command, _chatFileWithPath);
    }
    else if (starts_with(UserCommand::endChat, command) && ChatStatus::conversation == _chatStatus)
    {
         _log.info("TerminalFunctionality::runCommand() endChat command");
         _terminalCommand = std::make_unique<EndConversation>(command, chatInfo);
    }
    else if (starts_with(UserCommand::logout, command))
    {
        _log.info("TerminalFunctionality::runCommand() logout command");
        _terminalCommand = std::make_unique<LoggingOut>(command);
    }
    else if (starts_with(UserCommand::inviteUser, command))
    {
        _log.info("TerminalFunctionality::runCommand() invite user");
        _terminalCommand = std::make_unique<InviteSender>(command, chatInfo, _signalHandler, _informationPrinter);
    }
    else if (starts_with(UserCommand::startConversation, command))
    {
        _log.info("TerminalFunctionality::runCommand() start conversation");
        _terminalCommand = std::make_unique<InviteReceiver>(command, chatInfo, _signalHandler, _informationPrinter);
    }
    else
    {
        _log.info("TerminalFunctionality::runCommand() command NOT FOUND");
        return false;
    }

    return _terminalCommand->doCommand();
}

namespace
{
// waiting for GCC with C++20 support, function similar to it will be avaible in string class
bool starts_with(const std::string& starter, const std::string& ourString)
{
    auto iteratorOurString = ourString.begin();
    for(auto letter : starter)
    {
        if(letter == *iteratorOurString)
        {
            iteratorOurString++;
        }
        else
        {
            return false;
        }
    }
    return true;
}
} // namespace
