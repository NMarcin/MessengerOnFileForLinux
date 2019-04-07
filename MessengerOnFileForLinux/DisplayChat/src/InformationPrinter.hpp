#pragma once

#include <string>

class InformationPrinter
{
public:
    virtual void printInformation(const std::string&) const;
    virtual void printMainWindow() const;
    virtual void printRegistrationWindow() const;
    virtual void printSignInWindow() const;
};
