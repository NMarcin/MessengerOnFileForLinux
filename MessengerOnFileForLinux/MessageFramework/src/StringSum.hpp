#pragma once

#include <iostream>


class StringSumSquareBrackets
{
public:
    StringSumSquareBrackets() = default;
    ~StringSumSquareBrackets() = default;

    void sum(std::string s);
    std::string getSumedString();

private:
    std::string sumedString;
};
