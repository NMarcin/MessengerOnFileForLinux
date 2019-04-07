#include <SignInTestCore.hpp>

SignInTestFixture::SignInTestFixture()
    : signIn(informationPrinter)
    , registerUser(informationPrinter)
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
    registerUser.registerNewUser();
}

void SignInTestFixture::TearDown()
{
    FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED ,user);
}

