// MHP.h
// This is the class that describes a mancala heuristic program

#ifndef MHP_h
#define MHP_h

#include "util.h"
#include "node.h"
#include <cstdlib>

class MHP
{
public:
	MHP();
	~MHP();
	// creates a new node at the eop, returns the index of the new node
	int Add_Node(int value);

	// points the argth argument of node src to dest
	void Point_Arg(int arg, int src, int dest) { program[src]->args[arg] = dest; }

	// sets the node src to value 
	void Set_Value(int src, int value) { program[src]->value = value; }

	// gets the value of the node src
	int Get_Value(int src) { return program[src]->value; }

	// returns the argth argument of node src
	int Get_Arg(int src, int arg) { return program[src]->args[arg]; }

	// returns true if src is an atom, else returns false
	bool Is_Atom(int src) { return (program[src]->args[0] == -1); }

	// removes the sub MHP at src and returns it as sub_MHP
	int Remove_SubMHP(int src, MHP *sub_MHP);

	// adds the sub_MHP to the MHP where the 
	int Add_SubMHP(int src, MHP *sub_MHP);

	void Mutate();

	node *program[MAX_PROGRAM];		// stores the mancala heuristic program
	int eop;						// stores the end of program value
	int state;
};

#endif