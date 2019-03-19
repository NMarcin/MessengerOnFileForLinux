#pragma once

#include <gtest/gtest.h>

#include <ChatRequest.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <thread>

class MessageFixture : public ::testing::Test
{
public:
    MessageFixture();
    void SetUp();
    void TearDown();
    ~MessageFixture();

};
