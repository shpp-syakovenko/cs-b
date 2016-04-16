#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
#include "Calculator.h"

using namespace std;

// Pull the number from string.
double Calculator::number(){
    bool toggle = false;
    double afterPoint = 10.0;
    double res = 0;
    while(true){
        char c = expression[i];
        i++;
        if(c == '.'){  // If found point include toggle.
            toggle = true;
            continue;
        }

        if(toggle && (c >= '0' && c <= '9')){ // Add numbers after point.
            res = res +(c- '0')/afterPoint;
            afterPoint *=10.0;
            continue;
        }

        if(c >= '0' && c <= '9'){        // Add numbers.
            res = res * 10 + (c - '0');
        }else{
            i--;
            return res;
        }
    }
}

// The check expression on the brackets and if found brackets the computing expression in a brackets.
double Calculator::brackets(){
    char c = expression[i];
    i++;
    if(c == '('){
        double x = levelOne();
        i++;
        return x;
    }else{
        i--;
        return number();
    }

}
// The third level of the operators.
double Calculator::levelThree(){
    double x = brackets();

    while(true){
        char c = expression[i];
        i++;
        switch (c) {
        case '^':
            x = pow(x, brackets());
            break;
        case '$':
            x = sin(brackets());
            break;
        case '#':
            x = cos(brackets());
            break;
        case '@':
            x = sqrt(brackets());
            break;
        case '&':
            x = tan(brackets());
            break;
        case '!':
            x = factorial(x);
            break;
        default:
            i--;
            return x;
            break;
        }
    }
}
// The second level of the operators.
double Calculator::levelTwo(){
    double x = levelThree();

    while(true){
        char c = expression[i];
        i++;
        switch (c) {
        case '*':
            x*= levelThree();
            break;
        case '/':
        {
            double y = levelThree();
            if(y == 0){
                cout <<"ERROR: division by 0" << endl;
                return 0;
            }
            x /= y;
            break;
        }
        default:
            i--;
            return x;
            break;
        }
    }
}
// The first level of the operators.
double Calculator::levelOne(){
    double x = levelTwo();

    while(true){
        char c = expression[i];
        i++;
        switch (c) {
        case '-':
            x  -= levelTwo();
            break;
        case '+':
            x += levelTwo();
            break;
        default:
            i--;
            return x;
            break;
        }
    }
}

// The computing the factorial of a number
double Calculator::factorial(double x){
    double result = 1;
    for(int i = 1; i <= x; i++){
        result *= i;
    }
    return result;
}

// The return result of the expression.
double Calculator::result(string str){
    expression = str;
    i = 0;

    double result = levelOne();

    return result;
}
