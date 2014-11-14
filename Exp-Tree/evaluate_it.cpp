#include <iostream>
using namespace std;
#include "tokenlist.h"
#include "vartree.h"
#include "exprtree.h"

int evaluate(const char str[], VarTree &vars)
{
  TokenList l(str); // Declare and construct our linked list
  ExprNode *root;
  static int ans = 0;   // For handling previous answers
  
  ListIterator i = l.begin();
  
  if((!i.token().isInteger()) && (i.token().isOperator())) 
    { 
      Token newHead(ans);
      l.push_front(newHead);
      i = l.begin();
    }

  cout << "Infix: " << l << endl;
  
  doSum(i, root);          // Here begins the Conversion

  cout << "Expression Tree: " << *root << endl;

  return root->evaluate(vars);
}

void doSum(ListIterator &i, ExprNode *node)
{
  ExprNode *left, *right;
  string oper;
  
  doProduct(i, left);

  if(!i.ended())
    oper = i.token().tokenChar();
  
  while(oper == "+" || oper == "-")
    {
      i.advance();
      doProduct(i, right);
 
      left = new Operation(left, oper, right);
      if(!i.ended())
	oper = i.token().tokenChar();
    }
  node = left;
}

void doProduct(ListIterator & i, ExprNode *node)
{
  ExprNode *left, *right;
  string oper;

  doFactor(i, left);

  if(!i.ended())
    oper = i.token().tokenChar();

  while(oper == "*" || oper == "/" || oper == "%")
    {
      i.advance();
      doFactor(i, right);

      left = new Operation(left, oper, right);
      if(!i.ended())
	oper = i.token().tokenChar();
    }
  node = left;
}

void doFactor(ListIterator &i, ExprNode *node)
{
  ExprNode *left;

  if(i.token().tokenChar() == "(")
    {
      i.advance();
      doSum(i, left)
    }

  else
    {
      if(i.token().isInteger())
	{
	  left = new Value(i.token().integerValue());
	}
      else
	doAssign(i, left);
    }
  if(!i.ended())
    i.advance();
  node = left
}

void doAssign(ListIterator &i, ExprNode *node)
{
  ExprNode *left, *right;
  string eq;
  ListIterator temp = i;

  left = new Variable(i.token().tokenChar());
  if(!i.ended())
    i.advance();
  if(!i.ended())
    eq = i.token().tokenChar();
    
  if(eq == "=" && !i.ended())
    {
      while(eq == "=" && !i.ended())
	{
	  if(!i.ended())
	    i.advance();
	  if(!i.ended())
	    doSum(i, right);
	  left = new Operation(left, eq, right);
	  if(!i.ended())
	    eq = i.token().tokenChar();
	}
    }
  else if(!i.ended())
    i = temp;

  node = left;
}

void doCompare(ListIterator &i, ExprNode *node)
{
  ExprNode *test, *trueCase, *falseCase;
  string comp;

  
}
