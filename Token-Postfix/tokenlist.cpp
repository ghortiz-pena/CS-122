// Token List Implementation file
//
// This tokenizer will scan a character string representing
// an expression, and will return a list of tokens.
// --- only integers and operators are supported (no names)

// The standard C library has some useful functions for us
#include <string.h>
#include <ctype.h>

// And to get the definition of a token:
#include "tokenlist.h"

//  output operation
//  Display all of the tokens in the list
int readInt(const char str[], int &pos);

ostream& operator<<( ostream &stream, TokenList &t )
{
    ListElement *curr;
    for (curr = t.head; curr != NULL; curr = curr->next)
    {
      stream << " " << curr->token;
    }
    return stream;
}

TokenList::TokenList(const char str[])
{
  int pos = 0;
  int value;
  char c;
  Token *tok;
  
  
  head = tail = current = NULL;

  while(str[pos] != 0) // While we're not at the end of the end of the list
    {

      while(str[pos] == ' ') // We don't care about spaces
	pos++;
      
      if(isdigit(str[pos]))
	{
	  value = str[pos] - '0';
	  while(isdigit(str[pos+1])) // Do we have more than one digit?
	    {                        // If so, grab the next digit of our input
	      value = value * 10;
	      value = value + (str[pos + 1] - '0');
	      pos++;
	    }
	  tok = new Token(value);
	}
      else
	tok = new Token(str[pos]); // If str[pos] is not an integer, make an operator node

      if(str[pos]!=0)
	{
	  push_back(*tok); // Put the token at the end of the list
	  pos++; // check the next character in str
	}
    }  

}

void TokenList::push_front(Token t)
{
  struct ListElement *newelement = new ListElement;

  newelement->token = t;    // Token to add
  newelement->next = head;  // New list node; next points at old head
  
  head = newelement;      // Head now points at new element
}

void TokenList::push_back(Token t)
{
  struct ListElement *newelement = new ListElement;

  newelement->token = t;      // Token to add
  newelement->next = NULL;    // Last node; next points to nothing

  if(tail != NULL)
    tail->next = newelement;// Old tail points at our new tail
  else //if tail is NULL, our list is empty, so both head and tail need a value
    head = newelement;
  tail = newelement;        // Tail points to the node we just added
}

//  Creates an iterator to refer to the beginning of the list
ListIterator TokenList::begin()
{
    return ListIterator( this, head );
}

//  Creates an iterator to refer after the end of the list
ListIterator TokenList::end()
{
    return ListIterator( this, NULL );
}

Token TokenList::pop()
{
  Token t;
  t = head->token;
  ListElement *remove;
  remove = head;
  head = head->next;
  delete remove;

  return t;
}
