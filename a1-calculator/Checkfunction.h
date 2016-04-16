#include <iostream>
#include <string>

using namespace std;

#ifndef CHECKFUNCTION_H
#define CHECKFUNCTION_H


class CheckFunction
{
public:
    // Edit of the expression.
    string editExpression(string expression);

    // Check on the validity.
    bool validator(string expression);

private:
    // Clear all the spaces in the string.
    string cleanerOfSpaces(string expression);

    // If we find the wrong position of operators then return false.
    bool CheckCompatibilityOfOperator(string expression);

    // The method checks for correct location of operator with brackets
    bool checkWithoutBrackets(string expression);

    // Replace of the sin, cos, sqrt, tan to character $,#,@,& and replace "," on "."
    string subReplace(string expression);

    // Replace the variables a,b,c on the numbers.
    string replaceVariable(string expression);

    // The arrange the brackets.
    string insertBrackets(string expression);

    // Replace of the sin, cos, sqrt, tan to character $,#,@,&.
    string viewOfExpression(string expression);

};

#endif // CHECKFUNCTION_H
