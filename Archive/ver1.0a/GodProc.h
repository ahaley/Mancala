#ifndef GodProc_h
#define GodProc_h

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "util.h"
#include "Player.h"
#include "MHP.h"
#include "Interpreter.h"
#include "Translater.h"
#include "PlayingField.h"

using namespace std;

#define RAND_FROM_POOL static_cast<short>(static_cast<double>(rand())) / (static_cast<double>(RAND_MAX) * static_cast<double>(POOLSIZE - 1.0))

#define RAND_NODE(i) static_cast<short>((static_cast<double>(rand()) / static_cast<double>(INT_MAX)) * static_cast<double>(i))


class Player;

class GodProc
{
public:
	GodProc();

	// Fills the pool with randomly generated MHPs
	void Create_Random_Pool();

	// fills mprogram with a random MHP
	short Create_Random_MHP(MHP *mprogram, int depth_counter);

	void Battle_Strawman();

	void Test_Mechanics();

	void GP();

	void Print_Report(int report_num);

	MHP pool[POOLSIZE];
	Player *player_one;
	Player *player_two;
	Mancala *mancala;
	Interpreter interpreter;
	Translater translater;
};

#endif