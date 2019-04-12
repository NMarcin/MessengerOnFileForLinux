#pragma once

#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "NcursesPrintOperationWrapper.hpp"

class NcursesPrintOperationWrapperMock : public NcursesPrintOperationWrapper
{
public:
    MOCK_CONST_METHOD1(printInformationIntoMainWindow, void(const std::string&));
    MOCK_CONST_METHOD0(printMainWindow, void());
    MOCK_CONST_METHOD0(printRegistrationWindow, void());
    MOCK_CONST_METHOD0(printSignInWindow, void());
};
