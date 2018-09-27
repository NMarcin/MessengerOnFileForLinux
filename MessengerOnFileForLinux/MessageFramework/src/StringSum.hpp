#pragma once

#include <iostream>
#include <Logger.hpp>
#include <LogSpace.hpp>

class StringSumSquareBrackets
{
public:
    StringSumSquareBrackets() = default;
    ~StringSumSquareBrackets() = default;

    void sum(std::string s);
    std::string getSumedString();

private:
    std::string sumedString;

    Logger log_ {LogSpace::MessageFramework};
};
