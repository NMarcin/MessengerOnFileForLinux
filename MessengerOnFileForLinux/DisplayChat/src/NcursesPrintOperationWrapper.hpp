#pragma once

#include <string>

class NcursesPrintOperationWrapper
{
public:
    virtual void printInformationIntoMainWindow(const std::string&) const = 0;
    virtual void printMainWindow() const = 0;
    virtual void printRegistrationWindow() const = 0;
    virtual void printSignInWindow() const = 0;
};
