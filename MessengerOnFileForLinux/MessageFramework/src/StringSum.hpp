#pragma once

#include <iostream>
#include <Logger.hpp>
#include <LogSpace.hpp>

class StringSumSquareBrackets
{
public:
    StringSumSquareBrackets() = default;
    ~StringSumSquareBrackets() = default;
    StringSumSquareBrackets(StringSumSquareBrackets &&) = default;
    StringSumSquareBrackets& operator=(StringSumSquareBrackets &&) = default;
    StringSumSquareBrackets(const StringSumSquareBrackets &) = default;
    StringSumSquareBrackets& operator=(const StringSumSquareBrackets &) = default;

    void sum(const std::string& s);
    std::string getSumedString() const;

private:
    std::string sumedString;

    Logger log_ {LogSpace::MessageFramework};
};
