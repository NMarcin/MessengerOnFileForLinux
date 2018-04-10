#include <TerminalFunctionality.hpp>

#include <HistoryDowloander.hpp>
#include <UserCommand.hpp>


bool starts_with(const std::string toFind, const std::string ourString);

bool TerminalFunctionality::runCommand(std::string command)
{
    if(starts_with(UserCommand::historyDowloander, command))
    {
        terminalCommand_ = std::make_unique<HistoryDowloander>(command);
        return terminalCommand_->doCommand();
    }
    else
    {
        return false;   // TODO: kto obsluguje tego, ze nie ma takiej komendy?
    }
}

TerminalFunctionality::TerminalFunctionality()
{
    terminalCommand_ = nullptr;
}

TerminalFunctionality::~TerminalFunctionality()
{
    //NOOP
}



// waiting for GCC with C++20 support, function similar to it will be avaible in string class
bool starts_with(const std::string starter, const std::string ourString)
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
