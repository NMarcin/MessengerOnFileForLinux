#pragma once

#include <gtest/gtest.h>
#include <Message.hpp>
#include <memory>

class MessageFixture : public ::testing::Test
{
public:
    MessageFixture() = default;
    void SetUp();
    void TearDown() {};
    ~MessageFixture() = default;

        std::unique_ptr<std::string> expectedReadMessage;
        std::unique_ptr<std::string> expectedInviterMessage;
        std::unique_ptr<std::string> expectedRecipientMessage;
};
