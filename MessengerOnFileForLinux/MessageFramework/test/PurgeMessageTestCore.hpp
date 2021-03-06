#pragma once

#include <gtest/gtest.h>

#include "PurgeMessage.hpp"

class PurgeMessageFixture : public ::testing::Test
{
public:
    PurgeMessageFixture() = default;
    void SetUp();
    void TearDown() {}
    ~PurgeMessageFixture() = default;

    std::unique_ptr<std::string> _expectedPurgeMessage;
    std::unique_ptr<Message> _message;
};
