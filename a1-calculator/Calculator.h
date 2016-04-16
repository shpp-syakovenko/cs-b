#include <iostream>
#include <string>
using namespace std;

#ifndef CALCULATOR
#define CALCULATOR

class Calculator{
public:    
    /**
     * @param expression. The expression
     * @return  The return result of the expression.
     */
    double result(string expression);

private:
    // The expression in a string
    string expression;
    // The pointer on the character in a string.
    int i;

    // The first level of the operators.
    double levelOne();
    // The second level of the operators.
    double levelTwo();
    // The third level of the operators.
    double levelThree();

    // Pull the number from string.
    double number();
    // The check expression on the brackets and if found brackets the computing expression in a brackets.
    double brackets();
    // The computing the factorial of a number
    double factorial(double x);


};

#endif // CALCULATOR

