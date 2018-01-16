#pragma once
#include <string>

using namespace std;

class Math
{
public:
    static double add(double, double);
    static double deduct(double, double);
    static double multiply(double, double);
    static double divide(double, double);
    static double power(double, double);

    static double compute(char, double, double);

    static double parse(string);
    static double parse(const char*);

    static bool isnumber(string);
    static bool isnumber(const char*);

    static bool isoperator(char);
    static int getprecedence(char);
    static bool isleftassociative(char);
};
