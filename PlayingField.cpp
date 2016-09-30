#include "PlayingField.h"

PlayingField::PlayingField()
{
}


// This function plays a game of mancala between two players.
// The score of the first minus the second is returned.
int PlayingField::Play_Game(Player *player_1, Player *player_2)
{
	Mancala mancala;
	bool done = false;

	while (!done)
	{
		player_1->Play_Turn(&mancala);
		if (!(done = player_1->game_over(&mancala)))
		{
			player_2->Play_Turn(&mancala);
			done = player_2->game_over(&mancala);
		}
	}

	if (VERBOSE)
	{
		player_1->print_puzzle(&mancala);

		cout << "Game over!\n";

		if (mancala.board[P1MANCALA] > mancala.board[P2MANCALA])
		{
			cout << "Player 1 wins!\n";
		}
		else if (mancala.board[P1MANCALA] < mancala.board[P2MANCALA])
		{
			cout << "Player 2 wins!\n";
		}
		else
		{
			cout << "It's a tie!\n";
		}
	}
	return mancala.board[P1MANCALA] - mancala.board[P2MANCALA];
}

