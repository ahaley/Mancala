// Mancala.h
// Class that stores the mancala board

#ifndef Mancala_h
#define Mancala_h

#include "util.h"

class Mancala
{
public:
	Mancala() 
	{
		// initializes the board
		int i;
		for (i = P1S1; i <= P1S6; i++)
		{
			board[i] = BEGSIZESLOT;	
		}
		for (i = P2S1; i <= P2S6; i++)
		{
			board[i] = BEGSIZESLOT;
		}
		board[P1MANCALA] = 0;
		board[P2MANCALA] = 0;
	};

	// board is stored in a one dimensional array
	short board[BOARDSIZE];
};

#endif