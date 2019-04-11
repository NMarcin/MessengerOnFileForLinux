#pragma once

#include "Logger.hpp"
#include "LogSpace.hpp"

class StringSumSquareBrackets
{
public:
    StringSumSquareBrackets() = default;
    ~StringSumSquareBrackets() = default;
    StringSumSquareBrackets(StringSumSquareBrackets &&) = default;
    StringSumSquareBrackets& operator=(StringSumSquareBrackets &&) = default;
    StringSumSquareBrackets(const StringSumSquareBrackets &) = default;
    StringSumSquareBrackets& operator=(const StringSumSquareBrackets &) = default;

    void sum(std::string s);
    std::string getSumedString();

private:
    std::string _sumedString;

    Logger _log {LogSpace::MessageFramework};
};
