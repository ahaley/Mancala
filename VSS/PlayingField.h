// PlayingField.h
// Implements a game between two Mancala Players

#ifndef PlayingField_h
#define PlayingField_h

#include "Player.h"
#include "Mancala.h"

class PlayingField
{
public:
	PlayingField();

	// Plays a game of mancala between player_1 and player_2
	int Play_Game(Player *player_1, Player *player_2);


private:
};

#endif

