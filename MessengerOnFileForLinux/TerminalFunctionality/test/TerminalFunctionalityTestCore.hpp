#pragma once

#include <gtest/gtest.h>
#include "TerminalFunctionality.hpp"

class TerminalFunctionalityFixture : public ::testing::Test
{
public:
    TerminalFunctionalityFixture();
    void SetUp();
    void TearDown();
    ~TerminalFunctionalityFixture();
};
