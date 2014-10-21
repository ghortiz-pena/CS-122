// Simple Expression Evaluation 
// This program will evaluate simple arithmetic expressions
// represented as a linked-list of tokens.  Keyboard input
// will be accepted into a string, which will be converted
// into that linked list.
//
// If the first symbol in the input string is an operator,
// then the value of the previous expression will be taken
// as an implicit first operand.
//
// The expressions may consist of the following:
// -- integer values (which may have multiple digits)
// -- simple arithmetic operators ( +, -, *, /, % )
// -- matched parentheses for grouping

// This implementation consists of a set of mutually-recursive 
// functions. which will track the structure of the expression.
//
// A sum expression is the sum or difference of one or more products.
// A product expression is the product or quotient of one or more factors.
// A factor may be a number or a parenthesized sum expression.

#include <iostream>
using namespace std;
#include "tokenlist.h"
#include "vartree.h"

// Pre-condition: l.current is an integer or '('
void doSum(ListIterator &i, TokenList *pf);
// Post-condition: l.current is null or ')'

// Pre-condition: l.current is an integer or '('
void doProduct(ListIterator &i, TokenList *pf);
// Post-condition: there are no more contiguous multiplicative operators

// Pre-condition: l.current is an integer or '('
void doFactor(ListIterator &i, TokenList *pf);
// Post-condition: l.current is an operator or null

// i.token is a variable name
void postfixAssign(ListIterator &i, TokenList *pf);
// there are no more contiguous assignment operations

// i is iterating over a postfix expression
//int doAssign(ListIterator &i, VarTree &vars);
// vars now has the new variable(s)

int evaluate(const char str[], VarTree &vars)
{
  TokenList l(str); // Declare and construct our linked list
  TokenList *pf = new TokenList;    // List for postfix expression
  static int ans = 0;   // For handling previous answers
  
  ListIterator i = l.begin();
  
  if((!i.token().isInteger()) && (i.token().isOperator())) 
    { // Complicated condition: evaluates as true if l.head is an operator
      // but not a parenthesis. 
      // In this case, we want to push the previous answer to the front

      Token newHead(ans);
      l.push_front(newHead);
      i = l.begin();
    }

  cout << "Infix: " << l << endl;
  
  doSum(i, pf);          // Here begins the Conversion

  cout << "Postfix: " << *pf << endl;

  TokenList *stack = new TokenList; // Stack for holding operators
  ListIterator eval = pf->begin();  // Iterator to parse postfix expression
  Token left, right;                // Containers

  while(!eval.ended())
    {
      if(!eval.token().isOperator()) // While there are integers or variables, push them onto the stack
	{
	 
	  stack->push_front(eval.token());
	 
	}
      else
	{
	  right = stack->pop(); // grab the operands in order
	  left = stack->pop();
	  string op = eval.token().tokenChar();

	  // I don't know if there's an elegant way to do this. Maybe Write a function that does this?
	  // Need to make sure that each element gets parsed correctly
	  if(left.isInteger() && right.isInteger())
	    {
	      if(op == "+")
		left = (left.integerValue() + right.integerValue());
	      if(op == "-")
		left = (left.integerValue() - right.integerValue());
	      if(op == "*")
		left = (left.integerValue() * right.integerValue());
	      if(op == "/")
		left = (left.integerValue() / right.integerValue());
	      if(op == "%")
		left = (left.integerValue() % right.integerValue());
	  
	    }
	  else if(!left.isInteger() && right.isInteger())
	    {
	      if(op == "+")
		left = (vars.lookup(left.tokenChar()) + right.integerValue());
	      if(op == "-")
		left = (vars.lookup(left.tokenChar()) - right.integerValue());
	      if(op == "*")
		left = (vars.lookup(left.tokenChar()) * right.integerValue());
	      if(op == "/")
		left = (vars.lookup(left.tokenChar()) / right.integerValue());
	      if(op == "%")
		left = (vars.lookup(left.tokenChar()) % right.integerValue());
	      if(op == "=")		
		vars.assign(left.tokenChar(), right.integerValue());		
	    }
	  else if(left.isInteger() && !right.isInteger())
	    {
	      if(op == "+")
		left = (left.integerValue() + vars.lookup(right.tokenChar()));
	      if(op == "-")
		left = (left.integerValue() - vars.lookup(right.tokenChar()));
	      if(op == "*")
		left = (left.integerValue() * vars.lookup(right.tokenChar()));
	      if(op == "/")
		left = (left.integerValue() / vars.lookup(right.tokenChar()));
	      if(op == "%")
		left = (left.integerValue() % vars.lookup(right.tokenChar()));
	    }
	  else if(!left.isInteger() && !right.isInteger())
	    {
	      if(op == "+")
		left = (vars.lookup(left.tokenChar()) + vars.lookup(right.tokenChar()));
	      if(op == "-")
		left = (vars.lookup(left.tokenChar()) - vars.lookup(right.tokenChar()));
	      if(op == "*")
		left = (vars.lookup(left.tokenChar()) * vars.lookup(right.tokenChar()));
	      if(op == "/")
		left = (vars.lookup(left.tokenChar()) / vars.lookup(right.tokenChar()));
	      if(op == "%")
		left = (vars.lookup(left.tokenChar()) % vars.lookup(right.tokenChar()));
	      if(op == "=")
		vars.assign(left.tokenChar(), vars.lookup(right.tokenChar()));
	    }

	  stack->push_front(left);
	}
      eval.advance();
      
    }
  
  if(left.isInteger())
    ans = left.integerValue();
  else
    ans = vars.lookup(left.tokenChar());

  return ans;
}

void doSum(ListIterator &i, TokenList *pf)
{
  string oper;       // For holding the operator


  doProduct(i, pf); // Sum = product + product


  if(!i.ended())
    oper = i.token().tokenChar(); // Grab an operator, only if current != NULL
    
  while(((oper == "+") || (oper == "-")) && !i.ended() ) 
    {
      i.advance(); // Move to next token, an int or a '('
      doProduct(i, pf); 
    
      Token t(oper);
      pf->push_back(t); // Add the operator the the expression
      
      if(!i.ended())
	oper = i.token().tokenChar(); // Grab the next operator
	
    }

}

void doProduct(ListIterator &i, TokenList *pf) // Works exactly the same way as doSum(), except
{                           // here, left and right are factors
  int left, right;
  string oper;

  
  doFactor(i, pf); // product = factor * factor

  if(!i.ended())
    oper = i.token().tokenChar();
  while(((oper == "*") || (oper == "/") || (oper =="%")) && !i.ended())
    {
      i.advance();
      doFactor(i, pf);

      Token t(oper);
      pf->push_back(t);

      if(!i.ended())
	oper = i.token().tokenChar();
	
    }

}

void doFactor(ListIterator &i, TokenList *pf) // Grabs a factor; evaluates if needed; return
{
  Token left, op;
  // factor = int || factor = (int + int)

  if(i.token().tokenChar() == "(")
    {
      i.advance();     
      doSum(i, pf); 
    }
  else 
    {
      if(i.token().isInteger())
	{
	  left = i.token(); // grab the factor
	  pf->push_back(left);    // add it to the list
	}
      else
	{
	  postfixAssign(i, pf);
	}	
    }
  if(!i.ended())
    i.advance();

}
      
    
void postfixAssign(ListIterator &i, TokenList *pf)
{
  Token left, eq, right;
  
  ListIterator temp = i;
  

  left = i.token();
  pf->push_back(left);
  if(!i.ended())
    i.advance();
         
  if(!i.ended())
    eq = i.token();


  if(eq.tokenChar() == "=" && !i.ended())
    {
      while(eq.tokenChar() == "=" && !i.ended())
	{
	  if(!i.ended())
	    i.advance();
	  if(!i.ended())
	    doSum(i, pf);
	  pf->push_back(eq);
	  if(!i.ended())
	    eq = i.token();
	}
    }
  else if(!i.ended())
    i = temp;
    
}
