#include "stdafx.h"
#include "ShuntingYard.h"
#include <stack>
#include <cctype>
#include "Math.h"

using namespace std;

ShuntingYard::ShuntingYard()
{
}

ShuntingYard::~ShuntingYard()
{
}

stack<string> parse(string equation) {
    stack<string> output;
    stack<char> operators;

    string number = "";

    for (string::iterator it = equation.begin(); it != equation.end(); ++it)
    {
        char token = *it;

        if (isspace(token)) continue;

        if (isdigit(token) || token == '.') {
            number += token;
        }
        else if (!number.empty()) {
            output.push(number);
            number = "";
        }

        if (Math::isoperator(token)) {
            while (!operators.empty()) {
                char op = operators.top();
                int opPre = Math::getprecedence(op);
                int tokenPre = Math::getprecedence(token);
                if ((opPre > tokenPre) || (opPre == tokenPre && Math::isleftassociative(op)) && op != '(') {
                    operators.pop();
                    output.push(string(1, op));
                }
                else
                    break;
            }

            operators.push(token);
        }

        if (token == '(')
            operators.push(token);
        if (token == ')')
        {
            bool found = false;
            while (!operators.empty() && !found) {
                char op = operators.top();
                operators.pop();

                if (op != '(')
                    output.push(string(1, op));
                else
                    found = true;
            }

            if (!found)
                throw invalid_argument("mismatched parentheses");
        }
    }

    if (!number.empty()) {
        output.push(number);
        number = "";
    }

    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();

        if (op == '(' || op == ')')
            throw invalid_argument("mismatched parentheses");

        output.push(string(1, op));
    }

    return output;
}

double doRpnLeft(stack<string> input) {
    stack<string> reverseInput;
    while (!input.empty()) {
        reverseInput.push(input.top());
        input.pop();
    }

    stack<double> staging;

    while (!reverseInput.empty()) {
        string op = reverseInput.top();
        reverseInput.pop();

        if (Math::isnumber(op))
        {
            staging.push(Math::parse(op));
        }
        else if (Math::isoperator(op[0])) {
            double y = staging.top();
            staging.pop();
            double x = staging.top();
            staging.pop();

            staging.push(Math::compute(op[0], x, y));
        }
    }

    return staging.top();
}

double ShuntingYard::calculate(string equation)
{
    stack<string> sy = parse(equation);
    return doRpnLeft(sy);
}