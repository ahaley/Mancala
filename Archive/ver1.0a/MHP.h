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
	short Add_Node(char value);

	// points the argth argument of node src to dest
	void Point_Arg(short arg, short src, short dest) { program[src]->args[arg] = dest; }

	// sets the node src to value 
	void Set_Value(short src, char value) { program[src]->value = value; }

	// gets the value of the node src
	char Get_Value(short src) { return program[src]->value; }

	// returns the argth argument of node src
	short Get_Arg(short src, short arg) { return program[src]->args[arg]; }

	// returns true if src is an atom, else returns false
	bool Is_Atom(short src) { return (program[src]->args[0] == -1); }

	// removes the sub MHP at src and returns it as sub_MHP
	short Remove_SubMHP(short src, MHP *sub_MHP);

	// adds the sub_MHP to the MHP where the 
	short Add_SubMHP(short src, MHP *sub_MHP);

	void Mutate();

	node *program[MAX_PROGRAM];		// stores the mancala heuristic program
	unsigned short eop;				// stores the end of program value
	char state;
};

#endif