#include "Interpreter.h"

Interpreter::Interpreter()
{
	player = NULL;
}

void Interpreter::Set_Player(Player *player)
{
	this->player = player;
}

Interpreter::~Interpreter()
{

}

// Returns the heurstic value of the mancala board according to the MHP mprogram starting
// at program_counter.
double Interpreter::Interpret_MHP(MHP *mprogram, int program_counter, Mancala *mancala)
{
	if (mprogram->Is_Atom(program_counter))
	{
		// atomic program, return the value of the atom
		return static_cast<double>(mprogram->Get_Value(program_counter));
	}

	// retrieve the operation at the current program_counter
	short op = mprogram->Get_Value(program_counter);

	// get the pointer to the left argument
	short left_pc = mprogram->Get_Arg(program_counter, 0);

	// get the value of the MHP at the left argument recursively
	double left_value = Interpret_MHP(mprogram, left_pc, mancala);
	
	short right_pc;
	double right_value;

	switch(op)
	{

	case MANCALA:
		// The MANCALA operation is a unary operation that will return the
		// amount of stones in either the player's mancala if it's argument
		// is even or the opponent's mancala if it's argument is odd.
		 
		if (static_cast<short>(left_value) % 2 == 0)	
			return static_cast<double>(player->get_player_mancala(mancala));
		else
			return static_cast<double>(player->get_opponent_mancala(mancala));

		break;
	case SLOT_PLAYER:
		// The SLOT_PLAYER operation is a unary operation that will return the
		// slot of the player specified by it's argument.
		 
		return static_cast<double>(player->get_player_count(static_cast<short>(left_value), mancala));

		break;
	case SLOT_OPPONENT:
		// The SLOT_OPPONENT operation is a unary operation that will return the
		// slot of the opponent specified by it's argument.
		 
		return static_cast<double>(player->get_opponent_count(static_cast<short>(left_value), mancala));

		break;
	case EQUAL:
		// The EQUAL operation is a arithmetic binary operation that will return 
		// 1 if it's arguments are equal, else 0.
		 

		right_pc = mprogram->Get_Arg(program_counter, 1);
		
		right_value = Interpret_MHP(mprogram, right_pc, mancala);
	
		return static_cast<double>(static_cast<short>(left_value) == static_cast<short>(right_value));

		break;
	case GREATER_THAN:
		// The GREATER_THAN operation is a binary operation that will return 1 if the
		// left_value is larger than the right value, else 0

		right_pc = mprogram->Get_Arg(program_counter, 1);
		
		right_value = Interpret_MHP(mprogram, right_pc, mancala);
		
		return static_cast<double>(static_cast<short>(left_value) > static_cast<short>(right_value));

		break;
	case LESS_THAN:
		// The LESS_THAN operation is a binary operation that will return 1 is the
		// left_value is less than the right_value, else 0
	
		right_pc = mprogram->Get_Arg(program_counter, 1);
		
		right_value = Interpret_MHP(mprogram, right_pc, mancala);
		
		return static_cast<double>(static_cast<short>(left_value) < static_cast<short>(right_value));

		break;
	case NOT:
		// The NOT operation is a boolean unary operation that will return
		// 1 if it's argument is 0, else 0.
		 
		return static_cast<double>(static_cast<short>(left_value) == 0);

		break;
	case AND:
		// The AND operation is a boolean binary operation that will return
		// 1 if the logical anding of all it's arguments is 1, else 0.
		 
		right_pc = mprogram->Get_Arg(program_counter, 1);

		right_value = Interpret_MHP(mprogram, right_pc, mancala);
	
		return static_cast<double>(static_cast<short>(left_value) && static_cast<short>(right_value));

		break;
	case OR:
		// The OR operation is a boolean binary operation that will return
		// 1 if the logical oring of all it's argument is 1, else 0.
		 
		right_pc = mprogram->Get_Arg(program_counter, 1);

		right_value = Interpret_MHP(mprogram, right_pc, mancala);
	
		return static_cast<double>(static_cast<short>(left_value) || static_cast<short>(right_value));

		break;
	case ADD:
		// The ADD operation is an arithmetic binary operation that returns
		// the sum of all of it's arguments.
		 
		right_pc = mprogram->Get_Arg(program_counter, 1);

		right_value = Interpret_MHP(mprogram, right_pc, mancala);
	
		return static_cast<double>(left_value + right_value);

		break;
	case SUBTRACT:
		// The SUBTRACT operation is an arithmetic binary operation that returns
		// the difference of the first argument and the second argument.
		 
		right_pc = mprogram->Get_Arg(program_counter, 1);

		right_value = Interpret_MHP(mprogram, right_pc, mancala);
	
		return static_cast<double>(left_value - right_value);

		break;
	case MULTIPLY:
		// The MULTIPLY operation is an arithmetic binary operation that returns
		// the multiplication of all of it's arguments.
		 
		right_pc = mprogram->Get_Arg(program_counter, 1);

		right_value = Interpret_MHP(mprogram, right_pc, mancala);
	
		return static_cast<double>(left_value * right_value);

		break;
	case DIVIDE:
		// The DIVIDE operation is an arithmetic binary operation that returns
		// the ratio of the first argument to the second argument.
		 
		right_pc = mprogram->Get_Arg(program_counter, 1);

		right_value = Interpret_MHP(mprogram, right_pc, mancala);
	
		if (left_value == 0 || right_value == 0)	// safe division
			return 0;
		else
			return static_cast<double>(left_value / right_value);

		break;
	}
	return 0;
}

