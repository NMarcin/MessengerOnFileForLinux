#include "SignInTestCore.hpp"

SignInTestFixture::SignInTestFixture()
    : _signIn(_ncursesPrintOperationWrapperMock)
    , _registerUser(_ncursesPrintOperationWrapperMock)
{
    EXPECT_CALL(_ncursesPrintOperationWrapperMock, printInformationIntoMainWindow(_)).WillRepeatedly(Return());
    EXPECT_CALL(_ncursesPrintOperationWrapperMock, printMainWindow()).WillRepeatedly(Return());
    EXPECT_CALL(_ncursesPrintOperationWrapperMock, printRegistrationWindow()).WillRepeatedly(Return());
    EXPECT_CALL(_ncursesPrintOperationWrapperMock, printSignInWindow()).WillRepeatedly(Return());
}

SignInTestFixture::~SignInTestFixture()
{
    //NOOP
}

void SignInTestFixture::SetUp()
{
    std::istringstream stream("1\n1");
    std::cin.rdbuf(stream.rdbuf());
    _registerUser.registerNewUser();
}

void SignInTestFixture::TearDown()
{
    FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED ,_user);
}

