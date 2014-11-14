// Variable Tree Implementation File
// This is a simple binary search tree associating variables
// with integer values.
#include <iostream>
#include <string>
using namespace std;

#include "vartree.h"

//  recursiveAssign
//  A recursive tree-traversal function to assign to a variable.
//  Parameters:
//  	node	(modified TreeNode ptr)	tree to insert into
//  	name	(input string)		name of variable
//  	value	(input integer)		value to assign
//  NOTE: node May be a null pointer, indicating an empty tree
void VarTree::recursiveAssign( TreeNode *&root, string name, int value )
{
  if(root == NULL)
    root = new TreeNode(name, value);
  else if(root->name == name)
    root->value = value;
  else
    {
      if(name < root->name)
	recursiveAssign(root->left, name, value);
      else
	recursiveAssign(root->right, name, value);
    }

}

//  assign
//  Assigns a value to a variable.
//  If the variable does not yet exist, it is created.
//  Parameters:
//  	name	(input string)		name of variable
//  	value	(input integer)		value to assign
void VarTree::assign( string name, int value )
{
    recursiveAssign( root, name, value );
}

//  recursiveLookup
//  A recursive tree-traversal function to search for a variable.
//  If the variable does not exist, it is created with a value of 0.
//  Parameters:
//  	node	(modified TreeNode ptr)	tree to insert into
//  	name	(input string)		name of variable
//  	value	(output integer)	value of variable
//  NOTE: node May be a null pointer, indicating an empty tree
void VarTree::recursiveLookup( TreeNode *&root, string name, int &value )
{
  if(name == root->name)
    value = root->value;
  else if(root != NULL)
    {
      if(name < root->name)
	recursiveLookup(root->left, name, value);
      else
	recursiveLookup(root->right, name, value);
    }
  else
    {
      value = 0;
      root = new TreeNode(name, value);
    }
}

//  lookup
//  Searches for a variable to get its value
//  If the variable does not yet exist, it is created.
//  Parameters:
//  	name	(input char array)	name of variable
//  Returns:				value of variable
int VarTree::lookup( string name )
{
    int value;
    recursiveLookup( root, name, value );
    return value;
}
