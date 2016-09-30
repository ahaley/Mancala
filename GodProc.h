#ifndef GodProc_h
#define GodProc_h

#include <iostream>
#include <string>
#include <fstream>

#include <ctime>
#include "util.h"
#include "Player.h"
#include "MHP.h"
#include "Interpreter.h"
#include "Translater.h"
#include "PlayingField.h"


class GodProc
{
public:
	GodProc();
	~GodProc();

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

