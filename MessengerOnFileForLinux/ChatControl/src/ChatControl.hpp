#pragma once
#include <memory>
#include <thread>
#include <vector>
#include <signal.h>
#include <queue>
#include <ncurses.h>

#include <Sender.hpp>
#include <Receiver.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>

enum class MessageFlag
{
    readMessage,
    inviterMessage,
    recipientMessage
};

enum class ChatRole
{
    inviter,
    recipient
};


class ChatControl
{
public:
    ChatControl();
    ~ChatControl();

private:

    std::string chatFileWithPath_;
    MessageFlag messageFlag_;

    Logger log{LogSpace::ChatFile};
};
