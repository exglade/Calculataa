// Calculataa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "ShuntingYard.h"

using namespace std;

int main()
{
    // Prompt for equation.

    string equation = "";

    cout << "Equation: ";
    getline(cin, equation);

    // Process.

    ShuntingYard sy;
    cout << equation << " = " << sy.calculate(equation) << endl;

    // Exit prompt.

    getchar();

    return 0;
}