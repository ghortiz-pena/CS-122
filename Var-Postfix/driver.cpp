#include <iostream>
using namespace std;
#include "evaluate.h"
int main()
{
    char userInput[80];
    VarTree vars;		// initially empty tree

    cout << "Five = 2 + 3 : " << evaluate("Five = 2 + 3 ", vars) << endl;
    cout << "Five = 4 : " << evaluate(" * Five = 4",vars) << endl;
    cout << "Age = 3 * Five : " << evaluate("Age =3 *Five", vars) << endl;
    cout << endl << "Try one yourself:  ";
    cin.getline(userInput,80);
    cout << userInput << " = " << evaluate(userInput, vars) << endl;
    cout << endl << "Try another:  ";
    cin.getline(userInput,80);
    cout << userInput << " = " << evaluate(userInput, vars) << endl;
}
