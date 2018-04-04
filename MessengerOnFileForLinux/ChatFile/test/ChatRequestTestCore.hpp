#pragma once

#include <gtest/gtest.h>

#include <ChatRequest.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>

class ChatRequestFixture : public ::testing::Test
{
public:
    ChatRequestFixture();
    void SetUp();
    void TearDown();
    ~ChatRequestFixture();

    static void testSigusr1Handler(int sig_num, siginfo_t *info, void *context);
    static void initSigusr1Action();
    ChatRequest chatRequest;
    std::string user = getenv("USER");
};
