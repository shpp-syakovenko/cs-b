#include "Checkfunction.h"
#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
#include "Calculator.h"

using namespace std;


    // Clear all the spaces in the string.
    string CheckFunction::cleanerOfSpaces(string str){
        for(int j = 0; j < (int)str.length();j++){
            if(str[j] == ' '){
                str.erase(j,1);
                j--;
            }
        }
        return str;

    }

    // If we find the wrong position of operators then return false.
    bool CheckFunction::CheckCompatibilityOfOperator(string str){

        for(int j = 0; j < (int)str.length(); j++){

            if(str[j] == '*' && str[j+1] == '/'){
                cout << "ERROR: What's the matter with you? You introduced \" */ \"!!!" << endl;
                return false;
            }
            if(str[j] == '/' && str[j+1] == '*'){
                cout << "ERROR: Do you want to divide or multiply?  \" /* \"!!!" << endl;
                return false;
            }
            if(str[j] == '*' && str[j+1] == '*'){
                cout << "ERROR: \" ** \" Are you want multiply on multiply? You are crazy man!!! Try again." << endl;
                return false;
            }
            if(str[j] == '/' && str[j+1] == '/'){
                cout << "ERROR: \" // \" Are you want divide on divide? You are crazy man!!! " << endl;
                return false;
            }
            if(str[j] == '-' && str[j+1] == '*'){
                cout << "ERROR: What's the matter with you? You introduced. \" -* \"!!!" << endl;
                return false;
            }
            if(str[j] == '+' && str[j+1] == '*'){
                cout << "ERROR: What's the matter with you? You introduced. \" +* \"!!!" << endl;
                return false;
            }
            if(str[j] == '-' && str[j+1] == '/'){
                cout << "ERROR: What's the matter with you? You introduced.  \" -/ \"!!!" << endl;
                return false;
            }
            if(str[j] == '+' && str[j+1] == '/'){
                cout << "ERROR: What's the matter with you? You introduced. \" +/ \"!!!" << endl;
                return false;
            }
            if(str[j] == '^' && str[j+1] == '-'){
                cout << "ERROR: \" ^- \" What's the matter with you? Put brackets. \" ^(-number) \" !!!" << endl;
                return false;
            }
            if(str[j] == '-' && str[j+1] == '^'){
                cout << "ERROR: \" -^ \" What's the matter with you? What do you want?" << endl;
                return false;
            }
            if(str[j] == '^' && str[j+1] == '*'){
                cout << "ERROR: \" ^* \" What's the matter with you? What are you going to multiply? " << endl;
                return false;
            }
            if(str[j] == '^' && str[j+1] == '/'){
                cout << "ERROR: \" ^/ \" What's the matter with you? What are you going to divide?" << endl;
                return false;
            }
            if(str[j] == '^' && str[j+1] == '^'){
                cout << "ERROR: \" ^^ \" You are CRAZY?" << endl;
                return false;
            }
            if(str[j] == '*' && str[j+1] == '^'){
                cout << "ERROR: \" *^ \" What's the matter with you? What are you going to multiply? " << endl;
                return false;
            }
            if(str[j] == '/' && str[j+1] == '*'){
                cout << "ERROR: \" ^/ \" What's the matter with you? What are you going to divide?" << endl;
                return false;
            }
            if(str[j] == '!' && isdigit(str[j+1])){
                cout << "ERROR: \" \" !number \" \" What's the matter with you? Set \" number! \" " << endl;
                return false;
            }

        }

        return true;
    }

    //  The method checks for correct location of operator with brackets such as:: "/)*"   "*()(/"   "^)*"
    bool CheckFunction::checkWithoutBrackets(string str){

        for(int i = 0; i < (int)str.length();i++){  // The delete all brackets with expression.
            if(str[i] == '(' || str[i] == ')'){
                str.erase(i,1);
                i--;
            }
        }

        if(!CheckFunction::CheckCompatibilityOfOperator(str)){ // The check the correctness of the operators.
            return false;
        }

        return true;
    }




    // Replace of the sin, cos, sqrt, tan to character $,#,@,& and replace "," on "."
    string CheckFunction::subReplace(string str){

        while(str.find("sin") != string::npos){
        str = str.replace(str.find("sin"),3,"$");
        }
        while(str.find("cos") != string::npos){
        str = str.replace(str.find("cos"),3,"#");
        }
        while(str.find("sqrt") != string::npos){
        str = str.replace(str.find("sqrt"),4,"@");
        }
        while(str.find("tan") != string::npos){
        str = str.replace(str.find("tan"),3,"&");
        }
        while(str.find(",") != string::npos){
            str = str.replace(str.find(","),1,".");
        }
        return str;
    }

    // Replace the variables a,b,c on the numbers.
    string CheckFunction::replaceVariable(string str){
        string a = "null";
        string b = "null";
        string c = "null";

        while(str.find("a") != string::npos){

            if(isdigit(str[str.find("a")+1])){        // If after the variable "a" of the number is inserted between the "*"
                str.insert(str.find("a")+1,"*");
            }
            if(isdigit(str[str.find("a")-1])){        // If before the variable "a" of the number is inserted between the "*"
                str.insert(str.find("a"),"*");
            }

            if(a == "null"){
                cout << "Enter the value of the variable: a = ";
                getline(cin,a);
            }
            str = str.replace(str.find("a"),1,a);
        }


        while(str.find("b") != string::npos){

            if(isdigit(str[str.find("b")+1])){        // If after the variable "b" of the number is inserted between the "*"
                str.insert(str.find("b")+1,"*");
            }
            if(isdigit(str[str.find("b")-1])){        // If before the variable "b" of the number is inserted between the "*"
                str.insert(str.find("b"),"*");
            }

            if(b == "null"){
                cout << "Enter the value of the variable: b = ";
                getline(cin,b);
            }
            str = str.replace(str.find("b"),1,b);
        }


        while(str.find("c") != string::npos){

            if(isdigit(str[str.find("c")+1])){        // If after the variable "c" of the number is inserted between the "*"
                str.insert(str.find("c")+1,"*");
            }
            if(isdigit(str[str.find("c")-1])){        // If before the variable "c" of the number is inserted between the "*"
                str.insert(str.find("c"),"*");
            }

            if(c == "null"){
                cout << "Enter the value of the variable: c = ";
                getline(cin,c);                
            }
            str = str.replace(str.find("c"),1,c);
        }

        return str;
    }

    // The arrange the brackets.
    string CheckFunction::insertBrackets(string str){

        for(int j = 0; j < (int)str.length(); j++){ // We run on the string looking for the two operators who are not separated by brackets

            if((int)str[j] >= 42 && (int)str[j] <= 47 && (int)str[j + 1] >=42 && (int)str[j + 1] <= 47) { // If the current and the next character is an operator then put between the opening bracket.
                str.insert(j + 1,"(");

                for(int k = j+1; k < (int)str.length(); k++){             // We run on the string until you meet the number.

                    if(isdigit(str[k])){                                  // If character is number.

                        for(; k < (int)str.length(); k++){                // We run to in end of the number

                            if((!isdigit(str[k+1]) && str[k+1] != '.')){  // If after number are not the point and not the number set closed bracket.

                                str.insert(k+1,")");
                                k = (int)str.length();                    // We exit the double-loop and return to the position where to put the opening bracket.

                            }
                        }
                    }
                }
            }
        }
        return str;
    }

    // Replace of the sin, cos, sqrt, tan to character $,#,@,&.
    string CheckFunction::viewOfExpression(string str){

        while (str.find("$") != string::npos) {
            str = str.replace(str.find("$"),1,"sin");
        }
        while(str.find("#") != string::npos){
            str = str.replace(str.find("#"),1,"cos");
        }
        while(str.find("@") != string::npos){
            str = str.replace(str.find("@"),1,"sqrt");
        }
        while(str.find("&") != string::npos){
            str = str.replace(str.find("&"),1,"tan");
        }

        return str;
    }


    // Edit the expression to bring it into the right kind
    string CheckFunction::editExpression(string expression){

        expression = CheckFunction::cleanerOfSpaces(expression);

        if(!CheckFunction::CheckCompatibilityOfOperator(expression)){
            cout << "Please try again to enter." << endl << endl;
           return "Error";
        }
        if(!CheckFunction::checkWithoutBrackets(expression)){
            cout << "Please try again to enter." << endl << endl;
           return "Error";
        }
        expression = CheckFunction::subReplace(expression);

        expression = CheckFunction::replaceVariable(expression);

        expression = CheckFunction::insertBrackets(expression);

        // Show expression of the user.
        cout << endl << "Expressino: " << CheckFunction::viewOfExpression(expression) << endl;

        return expression;
    }

    // Check expression on validity.
    bool CheckFunction::validator(string str){

        if(str == "Error"){
            return false;
        }

        int i = 0;
        for(int j = 0; j < (int)str.length(); j++){ // Check the expression of the correct number of bracket
            if(str[j] == '(' ){
                i++;
            }
            else if(str[j] == ')'){
                i--;
            }
            if(i < 0){
                cout << "ERROR: You're trying to close a non-existent bracket!!! " << endl << endl;
                return false;
            }
        }
        if(i != 0){
            cout << "ERROR: Brackets are not correct!!! Try again." << endl << endl;
            return false;
        }

        for(int i = 0; i < (int)str.length(); i++){ // Check the expression on the unknown symbols.
            char c = str[i];

            if(!((c >= '!' && c <='9') || c == '@' || c == '^')){
                cout << "Error: Your expression contains unknown symbols!!!" << endl << endl;
                return false;
            }
        }

        if(!(str[str.length()-1] == ')' || isdigit(str[str.length()-1]) || str[str.length()-1] == '!')){
            cout << "Error: Your expression ends at: " << str[str.length()-1] << endl;
            return false;
        }
        return true;
    }






