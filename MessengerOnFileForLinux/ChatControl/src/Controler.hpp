#pragma once
#include <memory>

#include "TerminalControl.hpp"
#include "ConversationControl.hpp"
#include "Logger.hpp"
#include "LogSpace.hpp"
#include "SignalHandling.hpp"
#include "NcursesPrintOperationWrapper.hpp"

class Controler
{
public:
    void controlUserAction();

    Controler(const SignalHandler& signalHandler, const NcursesPrintOperationWrapper& informationPrinter);
    ~Controler() = default;

    Controler(Controler &&) = delete;
    Controler operator=(Controler &&) = delete;
    Controler(const Controler &) = delete;
    Controler operator=(const Controler &) = delete;


private:
    std::unique_ptr<ConversationControl> _conversationControl;
    const SignalHandler& _signalHandler;
    const NcursesPrintOperationWrapper& _informationPrinter;
    std::unique_ptr<TerminalControl> _terminalControl;

    Logger _log{LogSpace::ChatControl};
};
