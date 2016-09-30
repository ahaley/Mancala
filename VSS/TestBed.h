// TestBed.h
// Allows two MHPs to be tested against each other

#ifndef TestBed_h
#define TestBed_h

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "Player.h"
#include "Mancala.h"
#include "Translater.h"
#include "Interpreter.h"
#include "PlayingField.h"

class TestBed
{
public:
	void Run_Test();

	string Load_MHS(const char *filename);

private:

};

#endif

