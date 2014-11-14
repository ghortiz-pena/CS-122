#include <iostream>
using namespace std;
#include "tokenlist.h"
#include "exprtree.h"

void doSum(ListIterator &i, ExprNode *&node);
void doProduct(ListIterator &i, ExprNode *&node);
void doFactor(ListIterator &i, ExprNode *&node);
void doAssign(ListIterator &i, ExprNode *&node);
void doCompare(ListIterator &i, ExprNode *&node);
void doCall(ListIterator &i, ExprNode *&node);
void doDefine(ListIterator &i, FunctionDef &fmap);

int evaluate(const char str[], VarTree &vars, FunctionDef &fmap)
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

  
  if(i.token().tokenChar() == "deffn")
    {
      doDefine(i, fmap);
      root = new Value(0);
    }
  else
    doCompare(i, root);          // Here begins the Conversion
  
  cout << *root << endl;
  
  return root->evaluate(vars, fmap);
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
  else if(!i.ended() && (i.token().tokenChar() != "("))
    i = temp;
  else if(!i.ended() && (i.token().tokenChar() == "("))
    {
      i = temp;
      doCall(i, node);
    }
}

void doCompare(ListIterator &i, ExprNode *&test)
{
  ExprNode *trueCase, *falseCase, *right;
  string comp;

  doSum(i, test);
  if(!i.ended())
    {
      if(i.token().tokenChar() == ")")
	i.advance();
    }
  if(!i.ended() && i.token().isOperator())
    {
      comp = i.token().tokenChar(); 
      i.advance();
      doSum(i, right);
      test = new Operation(test, comp, right);
    }
  if(!i.ended() && (i.token().tokenChar() == "?" || i.token().isOperator()))
    {
      i.advance();
      doSum(i, trueCase);
    }
  if(!i.ended() && (i.token().isOperator() || i.token().tokenChar() == ":"))
    {
      i.advance();
      doSum(i, falseCase);
      test = new Conditional(test, trueCase, falseCase);
    }

}

void doCall(ListIterator &i, ExprNode *&node)
{
  string name;
  ExprNode *parameters[10];
  int p = 0;

  if(!i.ended())
    name = i.token().tokenChar();
  i.advance();
    if(!i.ended())
    doCompare(i, node);
  parameters[p] = node;
  p++;
  if(!i.ended()){
    while(!i.ended() && i.token().tokenChar() != ")")
      {
	if(!i.ended())
	  doCompare(i, node);
	parameters[p] = node;
	p++;
      }
  }

  for(; p < 10; p++)
    parameters[p] = NULL;
  node = new Function(name, parameters);
}

//pre-condition: i is on "deffn"

void doDefine(ListIterator &i, FunctionDef &fmap)
{
  string n;
  string parameters[10];
  ExprNode *body;
  int p = 0;

  i.advance(); // i is now on the function name

  if(!i.ended())
    n = i.token().tokenChar(); 


  i.advance(); // i is now on open paren of parameters
  i.advance(); // i is now on the first parameter
  if(!i.ended())
    parameters[p] = i.token().tokenChar();
  p++;
  i.advance(); // i is now on comma separating parameters or close paren
  while(i.token().tokenChar() == "," && !i.ended())
    {
      i.advance(); // i is now on next parameter
      if(!i.ended())
	parameters[p] = i.token().tokenChar();
      p++;
      i.advance(); // i is on new comma or close paren
    }
  i.advance(); // i is now on "="
  i.advance();
  
  if(!i.ended())
    doCompare(i, body);

  fmap[n].name = n;
  for(int i = 0; i < p; i++)
    {
      fmap[n].parameter[i] = parameters[i];
    }
  fmap[n].functionBody = body;
  fmap[n].locals = new VarTree();

  cout << *fmap[n].functionBody << endl;
  
}
