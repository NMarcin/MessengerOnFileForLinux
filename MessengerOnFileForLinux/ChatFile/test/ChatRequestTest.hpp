#pragma once
#include <gtest/gtest.h>

#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <ChatRequest.hpp>
#include <User.hpp>

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

