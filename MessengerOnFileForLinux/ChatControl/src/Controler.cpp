// dodac do cmakow

#include <Controler.hpp>
#include <TerminalControl.hpp>

#define ever (;;)

void Controler::controlUserAction()
{
    for ever
    {
        chatControl_ = std::make_unique<TerminalControl>();

        chatControl_->waitingInTerminal();
        //chatControl_->getChatData(); -> pobieranie ewentualnych danych, ktore musi przekazac

        chatControl_ = nullptr;
        //chatControl_ = std::make_unique<ConversationControl>(command, chatFileWithPath_);   // dodać kiedy będzie klasa mwoznia
    }
}

// w mainie bedzie taka kolejnosc:
// logowanie z ewentualna rejestracja
// controlUserAction
// zakonczenie chatu
