#pragma once

#include <string>

class InformationPrinter
{
public:
    virtual void printInformation(const std::string&) const = 0;
};
