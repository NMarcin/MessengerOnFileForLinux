#pragma once
// DODAC DO CMAKOW TEST
#include <memory>

#include <TerminalControl.hpp> // do usuniecia po podmianie <> w unique

class Controler
{
public:
    void controlUserAction();

private:
    std::unique_ptr<TerminalControl> chatControl_; // do podmienienia na <ChatControl>
};
