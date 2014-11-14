#include <iostream>
using namespace std;
#include "evaluate.h"

int main()
{
    char userInput[80];
    VarTree vars;		// initially empty tree
    FunctionDef funs;
    cout << "Define sqr" << endl;
    evaluate("deffn sqr(x) = x*x", vars, funs);
    cout << "define abs" << endl;
    evaluate("deffn abs(x) = x > 0 ? x : 0-x", vars, funs);
    cout << "define factorial" << endl;
    evaluate("deffn fact(n) = n <= 1 ? 1 : n * fact(n-1)", vars, funs );
    cout << "sqr(5): " << evaluate("sqr(5)", vars, funs) << endl;
    cout << "Three = abs(0-3): " << evaluate("Three =  abs(0-3) ",vars, funs) << endl;
    cout << "Fact(3): " << evaluate("fact(3)", vars, funs) << endl;
    cout << endl << "Try one yourself:  ";
    cin.getline(userInput,80);
    cout << userInput << " = " << evaluate(userInput, vars, funs) << endl;
    cout << endl << "Try another:  ";
    cin.getline(userInput,80);
    cout << userInput << " = " << evaluate(userInput, vars, funs) << endl;
}
