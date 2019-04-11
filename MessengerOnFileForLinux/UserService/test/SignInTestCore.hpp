#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "FileHandling.hpp"
#include "GlobalVariables.hpp"
#include "RegisterUser.hpp"
#include "SignIn.hpp"
#include "SignOut.hpp"
#include "NcursesPrintOperationWrapperMock.hpp"

using namespace ::testing;
class SignInTestFixture : public Test
{
public:
    SignInTestFixture();
    void SetUp();
    void TearDown();
    ~SignInTestFixture();

    const std::string _user = getenv("USER");
    SignIn _signIn;
    SignOut _signOut;
    RegisterUser _registerUser;
    NiceMock<NcursesPrintOperationWrapperMock> _ncursesPrintOperationWrapperMock;
};
