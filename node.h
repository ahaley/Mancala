// node.h
// This class represents a node of a Mancala Heuristic Program(MHP). 
// The fundamental data structure of an MHP is an array of class node.
// The value of the node is stored in the data member value, which 
// is of type char. The value represents either a function or data
// value. The argument(s) of the node are stored in the array args, 
// which reference the index of the argument in the array. If the node 
// is an atom then a -1 value will be stored in the 0th location of 
// the args array.

#ifndef NODE_H
#define NODE_H

#include "util.h"

class node
{
public:
	short value;				    
	short args[MAX_ARGS];							
};

#endif

