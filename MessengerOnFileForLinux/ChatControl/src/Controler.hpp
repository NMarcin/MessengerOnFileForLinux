#pragma once
// dodac do cmakow
#include<memory>

class Controler
{
public:
    void controlUserAction();

private:
    std::unique_ptr<ChatControl> chatControl_;
}
