#include <iostream>
using namespace std;
#include "tokenlist.h"
#include "exprtree.h"

void doSum(ListIterator &i, ExprNode *&node);
void doProduct(ListIterator &i, ExprNode *&node);
void doFactor(ListIterator &i, ExprNode *&node);
void doAssign(ListIterator &i, ExprNode *&node);
void doCompare(ListIterator &i, ExprNode *&node);


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

  
  doCompare(i, root);          // Here begins the Conversion
  
  cout << *root << endl;
  return root->evaluate(vars);
}

void doSum(ListIterator &i, ExprNode *&node)
{
  ExprNode *left, *right;
  string oper;
  
  doProduct(i, node);

  if(!i.ended())
    oper = i.token().tokenChar();
  
  while(oper == "+" || oper == "-")
    {
      i.advance();
      doProduct(i, right);

      node = new Operation(node, oper, right);
      if(!i.ended())
	oper = i.token().tokenChar();
      else
	oper = "Done";
    }
  }

void doProduct(ListIterator & i, ExprNode *&node)
{
  ExprNode *left, *right;
  string oper;

  doFactor(i, node);

  if(!i.ended())
    oper = i.token().tokenChar(); 
  while(oper == "*" || oper == "/" || oper == "%")
    {
      i.advance();
      doFactor(i, right);
      node = new Operation(node, oper, right);
      if(!i.ended())
	oper = i.token().tokenChar();
      else
	oper = "Done";
    }
}

void doFactor(ListIterator &i, ExprNode *&node)
{
  ExprNode *left;

  if(i.token().tokenChar() == "(")
    {
      i.advance();
      doSum(i, node);
    }

  else
    {
      if(i.token().isInteger())
	{
	  node = new Value(i.token().integerValue());
	}
      else if(!i.token().isOperator())
	doAssign(i, node);
      else
	doCompare(i, node);
    }
  if(!i.ended())
    i.advance();
}

void doAssign(ListIterator &i, ExprNode *&node)
{
  ExprNode *left, *right;
  string eq;
  ListIterator temp = i;

  node = new Variable(i.token().tokenChar());
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
	  node = new Operation(node, eq, right);
	  if(!i.ended())
	    eq = i.token().tokenChar();
	  else
	    eq = "Done";
	}
    }
  else if(!i.ended())
    i = temp;
}

void doCompare(ListIterator &i, ExprNode *&test)
{
  ExprNode *trueCase, *falseCase, *right;
  string comp;

  doSum(i, test);

  if(!i.ended())
    {
      comp = i.token().tokenChar(); 
      i.advance();
      doSum(i, right);
      test = new Operation(test, comp, right);
    }
  if(!i.ended() && i.token().tokenChar() == "?")
    {
      i.advance();
      doSum(i, trueCase);
    }
  if(!i.ended())
    {
      if(i.token().tokenChar() == ":")
	i.advance();
      
      doSum(i, falseCase);
      cout << *falseCase << endl;
      test = new Conditional(test, trueCase, falseCase);
    }

}
