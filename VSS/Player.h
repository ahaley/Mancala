// Player.h
// Encapsulates a Mancala Player. The mechanics of 
// playing Mancala are in this class. The alpha-beta
// search function is also located in this class. 

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "Interpreter.h"
#include "Mancala.h"
#include "MHP.h"
#include "util.h"

using namespace std;

class Interpreter;

class Player
{
public:
	Player(bool is_p1, int player_type);

	// makes decision of next move
	bool Play_Turn(Mancala *mancala);
	
	bool Play_Turn_Human(Mancala *mancala); // decides through user input
	bool Play_Turn_StrawMan(Mancala *mancala); // decides through random function
	bool Play_Turn_Informed(Mancala *mancala); // decides through MHP

	// recursive alpha-beta function
	double alpha_beta(Mancala mancala, double alpha, double beta, int level);

	double get_heuristic(Mancala *mancala);

	// board specific functions
	bool Make_Move(short slot, Mancala *mancala);
	bool Make_Move_P1(short slot, Mancala *mancala);
	bool Make_Move_P2(short slot, Mancala *mancala);

	// returns information about board

	bool game_over(Mancala *mancala);
	short get_count(short slot, Mancala *mancala);

	double get_player_count(int slot, Mancala *mancala);
	double get_opponent_count(int slot, Mancala *mancala);
	double get_player_mancala(Mancala *mancala);
	double get_opponent_mancala(Mancala *mancala);

	void print_puzzle(Mancala *mancala);

	// sets the MHP to be used with this player
	void install_MHP(MHP *mprogram);

	int ab_count;


private:
	bool is_p1;
	int player_type;
	MHP *mprogram;
	Interpreter *interpreter;	
};

#endif

