#pragma once
#include <ClasslessLogger.hpp>
#include <csignal>
#include <stdlib.h>

namespace SignalHandling
{
     void sigintHandlerInMainConsole(int signal);
     void sigintHandlerInChatConsole(int signal);
}
