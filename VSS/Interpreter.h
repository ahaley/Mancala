// Interpreter.h
// This program interprets a mancala heuristic language (MHP) structure.
// It returns a double value that weighs a Mancala structure against
// an MHP.

#ifndef Interpreter_h
#define Interpreter_h

#include <iostream>
#include "util.h"
#include "MHP.h"
#include "Mancala.h"
#include "Player.h"

using namespace std;

class Player;

class Interpreter
{
public:
	Interpreter();
	~Interpreter();
	
	void Set_Player(Player *player);

	// This function returns the heuristic value of the Mancala board
	// according to the MHP program beginning at the program_counter.
	double Interpret_MHP(MHP *mprogram, int program_counter, Mancala *mancala);

private:
	// This Player class pointer is needed because the player
	// has the knowledge of how to disect the Mancala board.
	Player *player;
};


#endif

