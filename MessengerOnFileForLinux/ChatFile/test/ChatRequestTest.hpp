#pragma once
#include <gtest/gtest.h>

#include <ChatRequest.hpp>

class ChatRequestFixture : public ::testing::Test
{
public:
    ChatRequestFixture();
    void SetUp();
    void TearDown();
    ~ChatRequestFixture();

    ChatRequest chatRequest;
    std::string user = getenv("USER");

};

