#pragma once

#include <string>

class InformationPrinter
{
public:
    void printInformation(const std::string&) const;
    void printMainWindow() const;
    void printRegistrationWindow() const;
    void printSignInWindow() const;
};
