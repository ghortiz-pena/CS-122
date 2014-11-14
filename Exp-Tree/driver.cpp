#include <iostream>
using namespace std;
#include "evaluate.h"
int main()
{
    char userInput[80];
    VarTree vars;		// initially empty tree

    cout << "A = 3: " << evaluate("A = 3 ", vars) << endl;
    cout << "B = 4 : " << evaluate("B = 4",vars) << endl;
    cout << "if A > B: C = 10; else: C = 20 : " << evaluate("A > B ? C = 10 : C = 20", vars) << endl;
    cout << endl << "Try one yourself:  ";
    cin.getline(userInput,80);
    cout << userInput << " = " << evaluate(userInput, vars) << endl;
    cout << endl << "Try another:  ";
    cin.getline(userInput,80);
    cout << userInput << " = " << evaluate(userInput, vars) << endl;
}
