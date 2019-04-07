#pragma once

#include <gtest/gtest.h>

#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <RegisterUser.hpp>
#include <SignIn.hpp>
#include <SignOut.hpp>
#include "InformationPrinterStub.hpp"

class SignInTestFixture : public ::testing::Test
{
public:
    SignInTestFixture();
    void SetUp();
    void TearDown();
    ~SignInTestFixture();

    const std::string user = getenv("USER");
    SignIn signIn;
    SignOut signOut;
    RegisterUser registerUser;
    InformationPrinterStub informationPrinter;
};
