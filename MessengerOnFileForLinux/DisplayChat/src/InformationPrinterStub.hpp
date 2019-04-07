#pragma once

#include <string>

#include "InformationPrinter.hpp"

class InformationPrinterStub : public InformationPrinter
{
public:
    void printInformation(const std::string&) const {}
    void printMainWindow() const {}
    void printRegistrationWindow() const {}
    void printSignInWindow() const {}
};

