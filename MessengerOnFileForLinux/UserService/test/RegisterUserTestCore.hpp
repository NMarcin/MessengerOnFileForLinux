#pragma once

#include <gtest/gtest.h>

#include "RegisterUser.hpp"
#include "SHA1.hpp"
#include "NcursesPrintOperationWrapperMock.hpp"

using namespace ::testing;

class RegisterUserTestFixture : public Test
{
public:
    RegisterUserTestFixture()
        : _registerUser(_ncursesPrintOperationWrapperMock)
    {
        EXPECT_CALL(_ncursesPrintOperationWrapperMock, printInformationIntoMainWindow(_)).WillRepeatedly(Return());
        EXPECT_CALL(_ncursesPrintOperationWrapperMock, printMainWindow()).WillRepeatedly(Return());
        EXPECT_CALL(_ncursesPrintOperationWrapperMock, printRegistrationWindow()).WillRepeatedly(Return());
        EXPECT_CALL(_ncursesPrintOperationWrapperMock, printSignInWindow()).WillRepeatedly(Return());
    }

    NiceMock<NcursesPrintOperationWrapperMock> _ncursesPrintOperationWrapperMock;
    RegisterUser _registerUser;
    SHA1 _sha1;
    std::string _user = getenv("USER");
};
