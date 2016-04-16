#include <iostream>
#include <string>
#include <Calculator.h>
#include <Checkfunction.h>
#include <cmath>
#include <sstream>


using namespace std;

/**
 * @brief tester. If test == res, Calculator passed the test
 * @param test  The expression
 * @param res   The result of the expression
 */
void tester(string test, double res){

    Calculator *expr = new Calculator;
    CheckFunction *checkFun = new CheckFunction;

    // The arrange of the brackets and check the of expression on validity.
    test = checkFun->editExpression(test);
    bool check = checkFun->validator(test);    

    if(check){
        // Evaluate the expression and returns the result
        double result = expr->result(test);

        if(result == res){
            cout << result << " = " << res << endl;
        }else{
            cout << "WARNING: " << result << " != " << res << endl;
        }
    }
    delete expr;
    delete checkFun;
}

int main()
{

    cout << "Welcome to the calculator from serglife!!!"<< endl;
    cout << "+ : plus" << endl;
    cout << "- : minus" << endl;
    cout << "* : multiply" << endl;
    cout << "/ : divide" << endl;
    cout << "sin(x) : sinus" << endl;
    cout << "cos(x) : cosine" << endl;
    cout << "tan(x) : tan" << endl;
    cout << "x^Y : x in degree y " << endl;
    cout << "x! : x factorial" << endl;
    cout << "a,b,c : variables" << endl << endl;


    Calculator *expr = new Calculator;
    CheckFunction *checkFun = new CheckFunction;
    bool debug = false;

    if(debug){
        tester("2+6",8);
        tester("2-2-6",-6);
        tester("2-6 + 4",0);
        tester("-2+6",4);
        tester("(5  + 1)^2",36);
        tester("2 +(3*2)+ 2*(2^3)",24);
        tester("4+(-2 -3) * (2^2)", -16);
        tester("2 * (2^3)", 16);
        tester("2*3^2",18);
        tester("2^3+(4*(-2))",0);
        tester("2-(-2)",4);
        tester("27/3^3",1);
        tester("(2+1)^3",27);
        tester("sqrt(81)",9);
        tester("3 * sqrt(36)",18);
        tester("sqrt((89-8))",9);
        tester("sqrt(3*3)",3);
        tester("(sqrt(36) + sqrt(81))",15);
        tester("sin(7)", 0.656987);
        tester("cos(1)", 0.540302);
        tester("tan(21)", -1.5275);
        tester("5!",120);
        tester("5*2*sqrt(15)+(((-2/5)-6^2)+10)/sin(20)",9.8126);
        tester("sin(5)/3+21-(32+cos(3)*2.5/(cos(21)/3))",-24.8755060896);
        tester("-34-(-9)*(2^4)/(sin(23^2)*sqrt(4^2))",4.44213062604);
        tester("3 * sin(420)  + cos((255+13)/10)",-2.5767);
        tester("5+5*3-(((123+12)*3)/13)",-11.1538);
        tester("-5+6*12*(2+8)",715);
        tester("sin3*cos3/3-tan4",-1.204390532);
        tester("2+-3+5--6/-6*-9+4--3+9-7",22);
        tester("24--4+--9*---4/--8*-4/-65+-6---84",-62.2769230769);


    }

    while(true){

        cout << "Enter of the number: ";
        string expression;
        getline(cin,expression);

        if(expression == ""){
            continue;
        }

        // The arrange of the brackets and check the of expression on validity.
        expression = checkFun->editExpression(expression);
        bool check = checkFun->validator(expression);

        // Show the result of the expression
        if(check){
            double result = expr->result(expression);
            cout << "result: " << result << endl << endl;
        }
    }

    delete expr;
    delete checkFun;
    return 0;

}

