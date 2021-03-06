// Expression Tree Implementation File
// These functions manage an expression tree that describes
// arithmetic expressions using integer variables and values.
// Some functions construct a tree from a character string that
// represents the expression, and then the tree can be traversed
// and evaluated.
#include <iostream>
#include <sstream>
using namespace std;
#include "exprtree.h"
#include "tokenlist.h"

// Outputting any tree node will simply output its string version
ostream& operator<<( ostream &stream, const ExprNode &e )
{
    return stream << e.toString();
}

// A Value is just an integer value -- easy to evaluate
// Unfortunately, the string class does not have a constructor for it
string Value::toString() const
{
    ostringstream convert;	// output string stream
    convert << value;		// 'output' into the stream
    return convert.str();	// and extract its string equivalent
}

int Value::evaluate( VarTree &v, FunctionDef &fmap ) const
{
    return value;
}

//  A variable is just an alphabetic string -- easy to display
//  TO evaluate, would need to look it up in the data structure
string Variable::toString() const
{
    return name;
}

int Variable::evaluate( VarTree &v, FunctionDef &fmap ) const
{
    return v.lookup( name );
}

string Operation::toString() const
{
  ostringstream convert;
  convert << left->toString() << " " << oper << " " << right->toString();
  return convert.str();
}

int Operation::evaluate(VarTree &v, FunctionDef &fmap) const
{
  if(oper == "+")
    return left->evaluate(v, fmap) + right->evaluate(v, fmap);
  else if(oper == "-")
    return left->evaluate(v, fmap) - right->evaluate(v, fmap);
  else if(oper == "*")
    return left->evaluate(v, fmap) * right->evaluate(v, fmap);
  else if(oper == "/")
    return left->evaluate(v, fmap) / right->evaluate(v, fmap);
  else if(oper == "%")
    return left->evaluate(v, fmap) % right->evaluate(v, fmap);
  else if(oper == ">")
    return left->evaluate(v, fmap) > right->evaluate(v, fmap);
  else if(oper == "<")
    return left->evaluate(v, fmap) < right->evaluate(v, fmap);
  else if(oper == ">=")
    return left->evaluate(v, fmap) >= right->evaluate(v, fmap);
  else if(oper == "<=")
    return left->evaluate(v, fmap) <= right->evaluate(v, fmap);
  else if(oper == "==")
    return left->evaluate(v, fmap) == right->evaluate(v, fmap);
  else if(oper == "!=")
    return left->evaluate(v, fmap) != right->evaluate(v, fmap);
  else if(oper == "=")
    {
      v.assign(left->toString(), right->evaluate(v, fmap));
      return v.lookup(left->toString());
    }
  else if(oper == "+=")
    {
      v.assign(left->toString(), left->evaluate(v, fmap) + right->evaluate(v, fmap));
      return v.lookup(left->toString());
    }
}

string Conditional::toString() const
{
  ostringstream convert;
  convert << test->toString() << " ? " << trueCase->toString();
  convert << " : " << falseCase->toString();
  return convert.str();
}


int Conditional::evaluate(VarTree &v, FunctionDef &fmap) const
{
  if(test->evaluate(v, fmap) == 1)
    return trueCase->evaluate(v, fmap);
  else
    return falseCase->evaluate(v, fmap);
}

string Function::toString() const
{
  ostringstream convert;
  convert << name << "(";
  for(int i = 0; parameters[i] != NULL; i++)
    {
      convert << *parameters[i];
      if(parameters[i+1] != NULL)
	convert << ", ";
    }
  convert << ")";
  return convert.str();
}



int Function::evaluate(VarTree &v, FunctionDef &fmap) const
{
  
  for(int p = 0; parameters[p] != NULL; p++)
    {
      fmap[name].locals->assign(fmap[name].parameter[p], parameters[p]->evaluate(v, fmap));
    }
  return fmap[name].functionBody->evaluate(*fmap[name].locals, fmap);
}
