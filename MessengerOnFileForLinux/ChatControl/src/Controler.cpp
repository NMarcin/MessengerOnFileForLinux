// dodac do cmakow

#include <Controler.hpp>


void Controler::controlUserAction()
{
    for ever
    {
        chatControl_ = std::make_unique<TerminalControl>(command, chatFileWithPath_);

        chatControl_->waitinginTerminal();
        chatControl_->getChatData();

        chatControl_ = nullptr;
        chatControl_ = std::make_unique<TerminalControl>(command, chatFileWithPath_);
    }
}

// w mainie bedzie taka kolejnosc:
// logowanie z ewentualna rejestracja
// controlUserAction
// zakonczenie chatu
