// dodac do cmakow

#include <Controler.hpp>
#include <TerminalControl.hpp>
#include <GlobalVariables.hpp>
#include <SignalHandling.hpp>

#define ever (;;)

void Controler::controlUserAction()
{
    _log.function("Controler::controlUserAction() started");

    for ever
    {
        TerminalControl::isWaitingForInvitation = true;

        _log.debug("Controler::controlUserAction() Loop begin ");
        _log.debug(("Controler::controlUserAction() isWaitingForInvitation = " + std::to_string(TerminalControl::isWaitingForInvitation)).c_str());
        _log.debug(("Controler::controlUserAction() isInvitationExist = " + std::to_string(TerminalControl::isInvitationExist)).c_str());

        std::thread waitForInvitation(_terminalControl->lookForInvitation);
        std::shared_ptr<ChatInformation> chatInfo = std::make_shared<ChatInformation>();
        _terminalControl = std::make_unique<TerminalControl>(ChatStatus::terminal, chatInfo);
        _terminalControl->waitingInTerminal();

        _log.debug("Controler::controlUserAction() waitingInTerminal finished");

        TerminalControl::isWaitingForInvitation = false;
        TerminalControl::isInvitationExist = false;
        waitForInvitation.join();

        _log.debug(("Controler::controlUserAction() isWaitingForInvitation = " + std::to_string(TerminalControl::isWaitingForInvitation)).c_str());
        _log.debug(("Controler::controlUserAction() isInvitationExist = " + std::to_string(TerminalControl::isInvitationExist)).c_str());

        if(not chatInfo->_chatPath.empty())
        {
            _log.info("Controler::controlUserAction() ConversationControl START()");
            _conversationControl = std::make_unique<ConversationControl>(chatInfo);
            _conversationControl->conversation();
            _conversationControl->conversationEpilog();
            _log.info("Controler::controlUserAction() ConversationControl END()");
        }
    }
}
