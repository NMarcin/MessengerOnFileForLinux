#pragma once
#include <csignal>
#include <stdlib.h>
#include <array>

namespace
{
static constexpr int NUMBER_OF_HANLING_POSIX_SIGNALS = 5;
}

namespace SignalHandling
{
void posixSignalHandlerInMainConsole(int signal);
void posixSignalHandlerInChatConsole(int signal);
void createPosixSignalsHandling(void(*handlingFunction)(int));

static constexpr std::array<int, NUMBER_OF_HANLING_POSIX_SIGNALS> posixSignalsCausingUnexpectedApplicationEndings{SIGINT,
                                                                                                                  SIGHUP,
                                                                                                                  SIGCONT,
                                                                                                                  SIGTERM,
                                                                                                                  0};
}
