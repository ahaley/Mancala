// Translater.h
// This class translaters between Mancala Heuristic String(MHS) to a
// Mancala Heuristic Program(MHP). An MHS is human readable string
// with a syntax that resembles lisp. The form of an MHS is 
// ( operation arg1 arg2 ... ). An MHP is a machine readable
// array implementation of the MHS. This class is only needed
// when we want to convert one into the other, so performance
// is not a terribly crucial factor.

#ifndef Translater_h
#define Translater_h

#include <iostream>
#include <string>
#include "util.h"
#include "MHP.h"

using namespace std;

class Translater
{
public:
	Translater();

	// MHP from the MHS s
	int Translate_MHS(string s, MHP *mprogram);

	// recursive function that returns a MHS from the MHP mprogram beginning at program_counter
	string Translate_MHP(MHP *mprogram, int program_counter, int program_depth);
	
	string Indent(int program_depth);

private:
	bool is_atomic(string s);
	
	string get_op(string s);

	string get_arg(string s, int n);

};

#endif

