#include <thread>

#include <MessageTestCore.hpp>

void MessageFixture::SetUp()
{
    expectedReadMessage = std::make_unique<std::string>("[0][2019-03-21 08:41:30][mnurzyns][test read message]");
    expectedInviterMessage = std::make_unique<std::string>("[1][2019-03-21 08:41:30][mnurzyns][test inviter message]");
    expectedRecipientMessage = std::make_unique<std::string>("[2][2019-03-21 08:41:30][mnurzyns][test recipient message]");
}
