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

// Pre-condition: l.current is an integer or '('
int doSum(TokenList &l);
// Post-condition: l.current is null or ')'

// Pre-condition: l.current is an integer or '('
int doProduct(TokenList &l);
// Post-condition: there are no more contiguous multiplicative operators

// Pre-condition: l.current is an integer or '('
int doFactor(TokenList &l);
// Post-condition: l.current is an operator or null

int evaluate(const char str[])
{
  TokenList l(str); // Declare and construct our linked list
  static int ans;   // For handling previous answers

  l.start();
  if((!l.nextToken().isInteger()) && (l.nextToken().tokenChar() != '(')) 
    { // Complicated condition: evaluates as true if l.head is an operator
      // but not a parenthesis. 
      // In this case, we want to push the previous answer to the front
      Token newHead(ans);
      l.push_front(newHead);
      l.start();
    }

  
  ans = doSum(l);          // Here begins the math
  
  return ans;
}

int doSum(TokenList &l)
{
  int left, right; // For holding values; ans = left + right until no more sums
  char oper;       // For holding the operator

  left = doProduct(l); // left can be a product expression

  if(!l.atEnd())
    oper = l.nextToken().tokenChar(); // Grab an operator, only if current != NULL
    
  while(((oper == '+') || (oper == '-')) && !l.atEnd() ) 
    {
      l.advance(); // Move to next token, an int or a '('
      right = doProduct(l); // right can also be a product expression
    
      if(oper == '-')
	right = -right;

      left = left + right;
      
      if(!l.atEnd())
	oper = l.nextToken().tokenChar(); // Grab the next operator
	
    }

  return left;
}

int doProduct(TokenList &l) // Works exactly the same way as doSum(), except
{                           // here, left and right are factors
  int left, right;
  char oper;
  
  left = doFactor(l); 

  if(!l.atEnd())
    oper = l.nextToken().tokenChar();
  while(((oper == '*') || (oper == '/') || (oper =='%')) && !l.atEnd())
    {
      l.advance();
      right = doFactor(l);

      if(oper == '*')
	left = left * right;
      if(oper == '/')
	left = left / right;
      if(oper == '%')
	left = left % right;

      if(!l.atEnd())
	oper = l.nextToken().tokenChar();
	
    }

  return left;
}

int doFactor(TokenList &l) // Grabs a factor; evaluates if needed; return
{
  int left;
  
  if(l.nextToken().tokenChar() == '(')
    {
      l.advance();     
      left = doSum(l); // "A factor may be a parenthesized sum expression"
    }
  else
    left = l.nextToken().integerValue();

  if(!l.atEnd())
    l.advance();

  return left;
}
      
    
