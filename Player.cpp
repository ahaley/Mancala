#include "Player.h"
#include <cfloat>

Player::Player(bool is_p1, int player_type)
{
	ab_count = 0;
	this->is_p1 = is_p1;
	this->player_type = player_type;
	interpreter = NULL;
	mprogram = NULL;
};


// Executes a turn according to the player_type
bool Player::Play_Turn(Mancala *mancala)
{
	switch(player_type)
	{
	case HUMAN:
		return Play_Turn_Human(mancala);
		break;
	case STRAWMAN:
		return Play_Turn_StrawMan(mancala);
		break;
	case INFORMED:
		return Play_Turn_Informed(mancala);
		break;
	}
	return false;
};



// Bases it's decision on human interface
bool Player::Play_Turn_Human(Mancala *mancala)
{
	short slot;
	bool done = false;

	do 
	{
		print_puzzle(mancala);

		if (is_p1)
			cout << "Player 1 ";
		else
			cout << "Player 2 ";

		cout << "Enter Slot#: ";
		cin >> slot;
		
		if (Make_Move(slot, mancala))
			done = true;
		else
			cout << "\nInvalid Slot, try again." << endl;
	}
	while (!done);
	
	return true;
};



// Plays according to the random number generator
bool Player::Play_Turn_StrawMan(Mancala *mancala)
{
	short slot;
	bool done = false;

	if (VERBOSE)
	{
		print_puzzle(mancala);
	}

	Mancala temp_mancala = *mancala;

	do
	{
		slot = static_cast<int>(rand() % 6) + 1;  // time to decide

		if (Make_Move(slot, &temp_mancala))
			done = true;
		else
			temp_mancala = *mancala;
	}
	while (!done);

	Make_Move(slot, mancala);

	if (VERBOSE)
	{
		if (is_p1)
		{
			cout << "Player 1:"; 
		}
		else
		{
			cout << "Player 2:";
		}
		cout << "Straw Man> Well Dorthy, I choose slot " << slot << endl;
	}
	return true;
};



// Plays according to an alpha-beta search
bool Player::Play_Turn_Informed(Mancala *mancala)
{
	double score;						// stores the current score
	double best_score = -DBL_MAX;		// stores the best score
	short best_slot;					// stores the best slot
	Mancala temp_mancala = *mancala;	// for testing the mancala waters

	if (VERBOSE)
		print_puzzle(mancala);

	for (int i = 1; i <= 6; i++)
	{
		if (Make_Move(i, &temp_mancala))
		{
			score = alpha_beta(temp_mancala, -DBL_MAX, DBL_MAX, 1);
			if (score > best_score)
			{
				best_score = score;
				best_slot = i;
			}
			temp_mancala = *mancala;
		}
	}

	Make_Move(best_slot, mancala);
	
	if (VERBOSE)
	{
		if (is_p1)
		{
			cout << "Player 1:";
		}
		else
		{
			cout << "Player 2:";
		}

		cout << "Informed> I choose slot " << best_slot << " with an alphabeta value of " << best_score << endl;

	}
	return true;
};



// Performs alpha-beta search on mancala
double Player::alpha_beta(Mancala mancala, double alpha, double beta, int level)
{
	ab_count++;
	
	if (level == ABDEPTH || game_over(&mancala))
	{
		// we've reached the end of the ab search, return the heuristic
		return get_heuristic(&mancala);
	}

	// we've still got more searching to go
	double alphabeta;
	Mancala temp_mancala = mancala;

	for (int i = 1; i <= 6; i++)
	{
		if (Make_Move(i, &temp_mancala))
		{
			// retrieve the alpha beta value of the child node
			alphabeta = alpha_beta(temp_mancala, alpha, beta, level + 1);
	
			if (MAXNODE)
			{
				// max node
				if (alpha < alphabeta)
				{
					if (alphabeta > beta)
					{
						return DBL_MAX;  // cutoff
					}
					alpha = alphabeta;
				}
			}
			else
			{
				// min node
				if (beta > alphabeta)
				{
					if (alpha > alphabeta)
					{
						return -DBL_MAX;  // cutuff
					}
					beta = alphabeta;
				}
			}
			temp_mancala = mancala;
		}
	}

	if (MAXNODE)
	{
		return alpha;
	}
	else
	{
		return beta;
	}
};

double Player::get_heuristic(Mancala *mancala)
{
	if (interpreter != NULL) 
		return interpreter->Interpret_MHP(mprogram, 0,  mancala);
	else
		return get_player_mancala(mancala);
};	


// Executes a move on mancala at slot
bool Player::Make_Move(short slot, Mancala *mancala)
{
	if (is_p1)
		return Make_Move_P1(slot, mancala);
	return Make_Move_P2(slot, mancala);
};

// Executes a move at slot on mancala as player 1
bool Player::Make_Move_P1(short slot, Mancala *mancala)
{
	slot--; // normalize, 1-6 ==> 0-5
	if (slot >= P1S1 && slot <= P1S6 && mancala->board[slot] != 0)
	{
		short hand = mancala->board[slot];
		mancala->board[slot] = 0;
		while (hand != 0)
		{
			slot++;

			if (slot == P2MANCALA) // skip past the opponent's mancala
			{
				slot = P1S1;
			}

			hand--;
			mancala->board[slot]++;
			if ((slot >= P1S1 && slot <= P1S6) &&			// handles landing on empty space
				(mancala->board[slot] == 1) &&				// opposite enemy stones
				(mancala->board[12 - slot] != 0) &&			
				(hand == 0))
			{
				mancala->board[P1MANCALA] += mancala->board[slot];
				mancala->board[P1MANCALA] += mancala->board[12 - slot];
				mancala->board[slot] = 0;
				mancala->board[12 - slot] = 0;
			}
		}
		if (game_over(mancala))
		{
			int i;
			for (i = P1S1; i <= P1S6; i++)
			{
				mancala->board[P1MANCALA] += mancala->board[i];
				mancala->board[i] = 0;
			}
			for (i = P2S2; i <= P2S6; i++)
			{
				mancala->board[P2MANCALA] += mancala->board[i];
				mancala->board[i] = 0;
			}
		}
		return true;
	}
	return false;
};

// executes a move at slot on mancala as player 2
bool Player::Make_Move_P2(short slot, Mancala *mancala)
{
	slot += 6; // normalize 1-6 ==> 7-12
	if (slot >= P2S1 && slot <= P2S6 && mancala->board[slot] != 0)
	{
		short hand = mancala->board[slot];
		mancala->board[slot] = 0;
		while (hand != 0)
		{
			// check to see if we need to cycle back to beginning of array
			if (slot == P2MANCALA) 
			{
				slot = P1S1;
			}
			else
			{
				slot++;
			}
			
			// skip past opponent's mancala
			if (slot == P1MANCALA)
			{
				slot = P2S1;
			}

			hand--;
			mancala->board[slot]++;
			if ((slot >= P2S1 && slot <= P2S6) &&
				(mancala->board[slot] == 1) &&			// handles landing on empty space
				(mancala->board[12 - slot] != 0) &&			// opposite enemy stones
				(hand == 0))
			{
				mancala->board[P2MANCALA] += mancala->board[slot];
				mancala->board[P2MANCALA] += mancala->board[12 - slot];
				mancala->board[slot] = 0;
				mancala->board[12 - slot] = 0;
			}
		}
		if (game_over(mancala))
		{
			int i;
			for (i = P1S1; i <= P1S6; i++)
			{
				mancala->board[P1MANCALA] += mancala->board[i];
				mancala->board[i] = 0;
			}
			for (i = P2S2; i <= P2S6; i++)
			{
				mancala->board[P2MANCALA] += mancala->board[i];
				mancala->board[i] = 0;
			}
		}
		return true;
	}
	return false;
};



void Player::print_puzzle(Mancala *mancala)
{
	int i;
	cout << endl;
	cout << "***************Mancala****************" << endl;
	cout << "*                                    *" << endl;

	cout << "*     ";
	for (i = P2S6; i >= P2S1; i--)
	{
		cout.width(4);	
		cout << mancala->board[i]; 
	}
	cout.width(8);
	cout << "*" << endl;
	cout << "*";

	cout.width(4);
	cout << mancala->board[P2MANCALA];
	cout.width(30);
	cout << mancala->board[P1MANCALA];
	cout.width(3);
	cout << "*" << endl;

	cout << "*     ";

	for (i = P1S1; i <= P1S6; i++)
	{
		cout.width(4);	
		cout << mancala->board[i];
	}

	cout.width(8);
	cout << "*" << endl;

	cout << "*                                    *\n";
	cout << "**************************************\n\n";

};

// ugly but efficient
bool Player::game_over(Mancala *mancala)
{
	if ((mancala->board[P1S1] + 
		 mancala->board[P1S2] + 
		 mancala->board[P1S3] + 
		 mancala->board[P1S4] + 
		 mancala->board[P1S5] + 
		 mancala->board[P1S6] == 0) ||
		(mancala->board[P2S1] + 
		 mancala->board[P2S2] + 
		 mancala->board[P2S3] + 
		 mancala->board[P2S4] + 
		 mancala->board[P2S5] + 
		 mancala->board[P2S6] == 0))
		 return true;
	return false;
};


// returns the size of the players slot specified by slot on mancala
short Player::get_count(short slot, Mancala *mancala)
{
	slot--;
	if (is_p1)
		return mancala->board[slot];
	else
		return mancala->board[slot + 7];
};


double Player::get_player_count(int slot, Mancala *mancala)
{
	if (slot < 1 || slot > 6)
		slot = abs(slot % 6 + 1);
	return (double)mancala->board[slot];
};


double Player::get_opponent_count(int slot, Mancala *mancala)
{
	if (slot < 1 || slot > 6)
		slot = abs(slot % 6 + 1);
	slot += 7;
	return (double)mancala->board[slot];
};


// returns the size of the player's mancala
double Player::get_player_mancala(Mancala *mancala)
{
	if (is_p1)
	{
		return (double)mancala->board[P1MANCALA];
	}
	return (double)mancala->board[P2MANCALA];
};


// returns the size of the enemies mancala
double Player::get_opponent_mancala(Mancala *mancala)
{
	if (is_p1)
	{
		return (double)mancala->board[P2MANCALA];
	}
	return (double)mancala->board[P1MANCALA];
};

void Player::install_MHP(MHP *mprogram)
{
	this->mprogram = mprogram;
	this->interpreter = new Interpreter();
	interpreter->Set_Player(this);
};


