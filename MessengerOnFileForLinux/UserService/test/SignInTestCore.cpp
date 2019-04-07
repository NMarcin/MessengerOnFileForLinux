#include <SignInTestCore.hpp>

SignInTestFixture::SignInTestFixture()
    : _signIn(_informationPrinter)
    , _registerUser(_informationPrinter)
{
    //NOOP
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

