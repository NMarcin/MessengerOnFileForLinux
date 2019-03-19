#pragma once

#include <gtest/gtest.h>
#include <PurgeMessage.hpp>

class PurgeMessageFixture : public ::testing::Test
{
public:
    PurgeMessageFixture();
    void SetUp();
    void TearDown();
    ~PurgeMessageFixture();

};
