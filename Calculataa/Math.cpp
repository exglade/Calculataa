#include "stdafx.h"
#include "Math.h"
#include <cmath>
#include <regex>

double Math::add(double x, double y)
{
    return x + y;
}

double Math::deduct(double x, double y)
{
    return x - y;
}

double Math::multiply(double x, double y)
{
    return x * y;
}

double Math::divide(double x, double y)
{
    return x / y;
}

double Math::power(double x, double y)
{
    return pow(x, y);
}

double Math::compute(char op, double x, double y)
{
    switch (op) {
    case'+': return add(x, y);
    case'-': return deduct(x, y);
    case'*': return multiply(x, y);
    case'/': return divide(x, y);
    case'^': return power(x, y);
    default:
        throw invalid_argument("invalid operation");
    }
}

double Math::parse(string number)
{
    return Math::parse(number.c_str());
}

double Math::parse(const char *number)
{
    if (!Math::isnumber(number))
        throw invalid_argument("invalid number");

    return strtod(number, NULL);
}

regex number_regex = regex("^[+-]?[0-9]+([.][0-9]+)?$");

bool Math::isnumber(string number)
{
    return Math::isnumber(number.c_str());
}

bool Math::isnumber(const char *number)
{
    return regex_match(number, number_regex);
}

char operators[][3] = { { '^', 4, 1 },{ '*', 3, 0 },{ '/', 3, 0 },{ '+', 2, 0 },{ '-', 2, 0 } };

bool Math::isoperator(char c)
{
    size_t ops_count = sizeof(operators) / sizeof(operators[0]);

    for (size_t i = 0; i < ops_count; i++)
    {
        if (c == operators[i][0])
            return true;
    }

    return false;
}

int Math::getprecedence(char c)
{
    size_t ops_count = sizeof(operators) / sizeof(operators[0]);

    for (size_t i = 0; i < ops_count; i++)
    {
        if (c == operators[i][0])
            return operators[i][1];
    }

    return 0;
}

bool Math::isleftassociative(char c)
{
    size_t ops_count = sizeof(operators) / sizeof(operators[0]);

    for (size_t i = 0; i < ops_count; i++)
    {
        if (c == operators[i][0])
            return operators[i][2] == 0 ? true : false;
    }

    return false;
}
