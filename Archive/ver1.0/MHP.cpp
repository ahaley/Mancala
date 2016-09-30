#include "MHP.h"


MHP::MHP()
{
	// initialize the end of program pointer
	eop = 0;
	state = READY;
}

MHP::~MHP()
{
	for (int i = 0; i < eop; i++)
	{
		delete program[i];
	}
}

// creates a new node at the eop or at a deleted node, returns the index of the new node
int MHP::Add_Node(int value)
{
	// check to make sure there are no deleted nodes
	for (int i = 0; i < eop; i++)
	{
		if (program[i]->value == DELETED)
		{
			// add the new node at this deleted node
			program[i]->value = value;
			program[i]->args[0] = -1;
			program[i]->args[1] = -1;
			return i;
		}
	}
	// no deleted nodes, new node created at eop and eop increased
	program[eop] = new node();
	program[eop]->value = value;
	program[eop]->args[0] = -1;
	program[eop]->args[1] = -1;
	eop++;
	return eop - 1;
}


// This recursive function removes a portion of code from the calling MHP and stores it
// in the parameter sub_MHP. It does this by recursively calling itself on each of the nodes
// of the sub MHP that is being copied and removed. The parameter src contains the index of
// the node specifically being copied and removed. 
int MHP::Remove_SubMHP(int src, MHP *sub_MHP)
{
	// create a new node in our sub_MHP and copy the current node's value to it
	int new_index = sub_MHP->Add_Node(Get_Value(src));
	
	// delete the value in the MHP
	Set_Value(src, DELETED);

	// if this node is an atom we're done
	if (Is_Atom(src))
		return new_index;

	// recursively call Remove_SubMHP on the first argument of the node
	int left_index = Remove_SubMHP(Get_Arg(src, 0), sub_MHP);
	
	// point the newly created sub_MHP node to it's first argument
	sub_MHP->Point_Arg(0, new_index, left_index);
	
	// kill the pointer of the MHP
	Point_Arg(0, src, -1);

	// checks to see if this is a unary op, if it is we're done
	if (Get_Arg(src, 1) == -1)
		return new_index;

	// recursively call Remove_SubMHP on the second argument of the node
	int right_index = Remove_SubMHP(Get_Arg(src, 1), sub_MHP);

	// point the newly created sub_MHP node to it's second argument
	sub_MHP->Point_Arg(1, new_index, right_index);

	// kill the pointer of the MHP
	Point_Arg(1, src, -1);

	// return the index of the newly created node of sub_MHP
	return new_index;
}


// adds the sub MHP to the MHP
int MHP::Add_SubMHP(int src, MHP *sub_MHP)
{
	// create a new node at the current index with the value of the sub_MHP
	int new_index = Add_Node(sub_MHP->Get_Value(src));

	// check to see if this node is an atom, if so then we are done
	if (sub_MHP->Is_Atom(src))
		return new_index;

	// recursively copy the left portion of the sub_MHP to the MHP
	int left_index = Add_SubMHP(sub_MHP->Get_Arg(src, 0), sub_MHP);

	// point the current node to the newly constructed left tree
	Point_Arg(0, new_index, left_index);

	// check to see if op is unary, if so then we are done
	if (sub_MHP->Get_Arg(src, 1) == 1)
		return new_index;

	// recursively copy the right portion of the sub_MHP to the MHP
	int right_index = Add_SubMHP(sub_MHP->Get_Arg(src, 1), sub_MHP);

	// point the current node to the newly constructed right tree
	Point_Arg(1, new_index, right_index);

	// return the index of the current node
	return new_index;
}

void MHP::Mutate()
{
	int src = (int)((double)rand() / (double)RAND_MAX * eop);
	int val = (int)(((double)rand() / (double)RAND_MAX) * 10);
	Set_Value(src, val);
}
