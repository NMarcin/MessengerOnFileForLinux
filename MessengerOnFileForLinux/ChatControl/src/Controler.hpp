#pragma once
#include <memory>

#include <TerminalControl.hpp>
#include <ConversationControl.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>


class Controler
{
public:
    void controlUserAction();

    Controler() = default;
    ~Controler() = default;

    Controler(Controler &&) = delete;
    Controler operator=(Controler &&) = delete;
    Controler(const Controler &) = delete;
    Controler operator=(const Controler &) = delete;


private:
    std::unique_ptr<TerminalControl> terminalControl_;
    std::unique_ptr<ConversationControl> conversationControl_;

    Logger log_{LogSpace::ChatControl};
};
