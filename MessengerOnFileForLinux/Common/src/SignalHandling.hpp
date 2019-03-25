#pragma once
#include <csignal>
#include <stdlib.h>
#include <array>

namespace SignalHandling
{
     void posixSignalHandlerInMainConsole(int signal);
     void posixSignalHandlerInChatConsole(int signal);
     void createPosixSignalsHandling(void(*handlingFunction)(int));

     static constexpr std::array<int, 6> posixSignalsCausingUnexpectedApplicationEndings{SIGINT,
                                                                                    SIGHUP,
                                                                                    SIGCONT,
                                                                                    SIGTERM,
                                                                                    0};


namespace NCurses
{
     void resizeHandlerInMainWindow(int signal);
     void resizeHandlerInRegistrationWindow(int signal);
     void resizeHandlerInSignInWindow(int signal);
     void resizeHandlerInChatWindow(int signal);
} //NCurses
} //SignalHandling
