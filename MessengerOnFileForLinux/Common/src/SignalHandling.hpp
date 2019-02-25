#pragma once
#include <csignal>
#include <stdlib.h>
#include <array>

namespace SignalHandling
{
     void posixSignalHandlerInMainConsole(int signal);
     void posixSignalHandlerInChatConsole(int signal);
     void createPosixSignalsHandling(void(*handlingFunction)(int));

     static constexpr std::array<int, 6> signalsCausingUnexpectedApplicationEndings{SIGINT,
                                                                                    SIGHUP,
                                                                                    SIGCONT,
                                                                                    SIGTERM,
                                                                                    0};
}
