// dodac do cmakow

#include <Controler.hpp>
#include <TerminalControl.hpp>

#define ever (;;)

void Controler::controlUserAction()
{
    for ever
    {
        terminalControl_ = std::make_unique<TerminalControl>();
        terminalControl_->waitingInTerminal();
        auto chatData = terminalControl_->getChatData();    // TODO mnurzyns zrobic to ładniej na zasadzie shared_ptr -> do zastanowienia sie

        conversationControl_ = std::make_unique<ConversationControl>();   // TODO mwozniak dodac konstruktor, ktory bierze chatData i wpisac sobie z powyzszego auto
        conversationControl_->conversation();
        conversationControl_->conversationEpilog();
    }
}

// w mainie bedzie taka kolejnosc:
// logowanie z ewentualna rejestracja
// controlUserAction
// zakonczenie chatu
