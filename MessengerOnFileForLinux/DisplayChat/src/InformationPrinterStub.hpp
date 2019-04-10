#pragma once

#include <string>

#include "InformationPrinter.hpp"

class InformationPrinterStub : public InformationPrinter
{
public:
    void printInformation(const std::string&) const final {}
    void printMainWindow() const final {}
    void printRegistrationWindow() const final {}
    void printSignInWindow() const final {}
};

