#include "Translater.h"


Translater::Translater()
{
};

// translates a Mancala Heuristic String(MHS) to a Mancala Heuristic Program(MHP)
int Translater::Translate_MHS(string s, MHP *mprogram)
{

	if (is_atomic(s))
	{
		return mprogram->Add_Node(atoi(s.c_str()));
	}

	string s_op = get_op(s);
	int op;
	int current_node;
	int arg1_node;
	int arg2_node;

	if (s_op == "MANCALA")
	{
		op = MANCALA;
		current_node = mprogram->Add_Node(op);
	}
	else if (s_op == "SLOT_PLAYER")
	{
		op = SLOT_PLAYER;
		current_node = mprogram->Add_Node(op);
	}
	else if (s_op == "SLOT_OPPONENT")
	{
		op = SLOT_OPPONENT;
		current_node = mprogram->Add_Node(op);
	}
	else if (s_op == "NOT")
	{
		op = NOT;
		current_node = mprogram->Add_Node(op);
	}
	else if (s_op == "EQUAL")
	{
		op = EQUAL;
		current_node = mprogram->Add_Node(op);
	}
	else if (s_op == "GREATER_THAN")
	{
		op = GREATER_THAN;
		current_node = mprogram->Add_Node(op);
	}
	else if (s_op == "LESS_THAN")
	{
		op = LESS_THAN;
		current_node = mprogram->Add_Node(op);
	}
	else if (s_op == "AND")
	{
		op = AND;
		current_node = mprogram->Add_Node(op);
	}
	else if (s_op == "OR")
	{
		op = OR;
		current_node = mprogram->Add_Node(op);
	}
	else if (s_op == "ADD")
	{
		op = ADD;
		current_node = mprogram->Add_Node(op);
	}
	else if (s_op == "SUBTRACT")
	{
		op = SUBTRACT;
		current_node = mprogram->Add_Node(op);
	}
	else if (s_op == "MULTIPLY")
	{
		op = MULTIPLY;
		current_node = mprogram->Add_Node(op);
	}
	else if (s_op == "DIVIDE")
	{
		op = DIVIDE;
		current_node = mprogram->Add_Node(op);
	}


	switch(op)
	{
	case MANCALA:
	case SLOT_PLAYER:
	case SLOT_OPPONENT:
	case NOT:
		// one argument functions
		arg1_node = Translate_MHS(get_arg(s, 1), mprogram);
		mprogram->Point_Arg(0, current_node, arg1_node);
		break;
	case EQUAL:
	case GREATER_THAN:
	case LESS_THAN:
	case AND:
	case OR:
	case ADD:
	case SUBTRACT:
	case MULTIPLY:
	case DIVIDE:
		// two argument functions
		arg1_node = Translate_MHS(get_arg(s, 1), mprogram);
		arg2_node = Translate_MHS(get_arg(s, 2), mprogram);
		mprogram->Point_Arg(0, current_node, arg1_node);
		mprogram->Point_Arg(1, current_node, arg2_node);
		break;
	}
	return current_node;
};

// translates a Mancala Heuristic Program(MHP) to a Mancala Heuristic String(MHS)
string Translater::Translate_MHP(MHP *mprogram, int program_counter, int program_depth)
{
	if (mprogram->Is_Atom(program_counter))
	{
		char *temp;
		temp = new char(10);
		temp = itoa(mprogram->Get_Value(program_counter), temp, 10);
		return temp;
	}

	int function = mprogram->Get_Value(program_counter);
	string function_name;
	bool is_two;

	switch(function)
	{
		
	case MANCALA:
		function_name = "MANCALA";
		is_two = false;
		break;
	case SLOT_PLAYER:
		function_name = "SLOT_PLAYER";
		is_two = false;
		break;
	case SLOT_OPPONENT:
		function_name = "SLOT_OPPONENT";
		is_two = false;
		break;
	case NOT:
		function_name = "NOT";
		is_two = false;
		break;
	case EQUAL:
		function_name = "EQUAL";
		is_two = true;
		break;
	case GREATER_THAN:
		function_name = "GREATER_THAN";
		is_two = true;
		break;
	case LESS_THAN:
		function_name = "LESS_THAN";
		is_two = true;
		break;
	case AND:
		function_name = "AND";
		is_two = true;
		break;
	case OR:
		function_name = "OR";
		is_two = true;
		break;
	case ADD:
		function_name = "ADD";
		is_two = true;
		break;
	case SUBTRACT:
		function_name = "SUBTRACT";
		is_two = true;
		break;
	case MULTIPLY:
		function_name = "MULTIPLY";
		is_two = true;
		break;
	case DIVIDE:
		function_name = "DIVIDE";
		is_two = true;
		break;
	}

	int left = mprogram->Get_Arg(program_counter, 0);
	if (!is_two)
	{
		// handles the case when the function is a unary operation
		return "(" + function_name + "\n" + Indent(program_depth) + Translate_MHP(mprogram, left, program_depth + 1) + ")";
	}
	
	// handles the case when the function is a binary operation
	int right = mprogram->Get_Arg(program_counter, 1);
	return "(" + function_name + "\n" + Indent(program_depth) + Translate_MHP(mprogram, left, program_depth + 1) + "\n" + Indent(program_depth) + Translate_MHP(mprogram, right, program_depth + 1) + ")";
}


// Returns true is s is atomic, false otherwise
bool Translater::is_atomic(string s)
{
	if (s[0] != '(' && s[s.length() - 1] != ')')
		return true;
	return false;
};

string Translater::Indent(int program_depth)
{
	string tabs;
	for (int i = 0; i < program_depth; i++)
	{
		tabs += "  ";
	}
	return tabs;
}


// Returns the top level operation of s
string Translater::get_op(string s)
{
	return get_arg(s, 0);
};
	

// Returns the nth argument of s, 0 returns the operator
// s must be in form ( operator arg1 arg2 ... )
string Translater::get_arg(string s, int n)
{
	if (s[0] != '(')
	{
		return s;
	}

	int i = 1;
	int start_arg;
	int end_arg;
	int paren_count = 0;
	bool in_arg = false;
	bool is_atom = false;
	int arg_count = 0;
	string arg_list[MAX_ARGS + 1];

	/* Note that this method of retrieving an argument is
	 * incredibly inefficient. Each time we want to retrieve
	 * an argument we have to rebuild an array of the arguments
	 * of the list. This will have to be addressed later. --(2/26/03)
	 */

	while (i < s.length())
	{
		if (!in_arg)
		{
			if (s[i] != ' ')
			{
				is_atom = (s[i] != '(');
				start_arg = i;
				in_arg = true;
			}
		}
		else
		{
			if (is_atom)
			{
				if (s[i] == ' ' || s[i] == '(' || s[i] == ')')
				{
					end_arg = i;
					arg_list[arg_count++] = s.substr(start_arg, end_arg - start_arg);
					is_atom = in_arg = false;
				}
			}
			else if (s[i] == '(')
			{
				paren_count++;
			}
			else if (s[i] == ')')
			{
				if (paren_count == 0)
				{
					end_arg = ++i;
					arg_list[arg_count++] = s.substr(start_arg, end_arg - start_arg);
					in_arg = false;
				}
				else
				{
					paren_count--;
				}
			}
		}
		i++;
	}
	return arg_list[n];
};