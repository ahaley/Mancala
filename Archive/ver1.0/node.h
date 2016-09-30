// node.h
// This is a single atom in the mancala heuristic program
// It can either be a function or a value

#ifndef node_h
#define node_h

#include "util.h"

class node
{
public:
	short value;				// represents a function or data value
	int args[MAX_ARGS];		// indexes the arguments of this node
								// if the 0th argument is -1, this
								// node contains a data value
};

#endif