#pragma once

#include <gtest/gtest.h>
#include <Message.hpp>

class MessageFixture : public ::testing::Test
{
public:
    MessageFixture();
    void SetUp();
    void TearDown();
    ~MessageFixture();

};
