//  Token Implementation file
//  This stores some of the more complicated features of the token object,
//  that would not be compiled in-line.

#include "token.h"

bool Token::isOperator()
{
  bool why;
  string ops = "+-*/%=";

  for(int i = 0; i < 6; i++)
    why += (oper[0] == ops[i]);

  return why;
}

ostream& operator<<( ostream &stream, Token &t)
{
    if (t.isNull())
	return stream << "(null)";
    if (t.isInteger())
	return stream <<  t.value ;
    else return stream <<  t.oper ;
}
