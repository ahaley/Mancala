#ifndef util_h
#define util_h

#include <cstdlib>

// Board specific constants
#define BOARDSIZE		14
#define P1S1			0
#define P1S2			1
#define P1S3			2
#define P1S4			3
#define P1S5			4
#define P1S6			5
#define P1MANCALA		6
#define P2S1			7
#define P2S2			8
#define P2S3			9
#define P2S4			10
#define P2S5			11
#define P2S6			12
#define P2MANCALA		13

#define BEGSIZESLOT		3

// Player specific constants
#define PLAYER1_TYPE	HUMAN
#define PLAYER2_TYPE	INFORMED

#define HUMAN			0
#define STRAWMAN		1
#define INFORMED		2

#define VERBOSE			false
#define GPMODE			true

// AI specific constants
#define ABDEPTH			4
#define MAXNODE			(level % 2 == 0)

// Constants for the mancala heuristic language
#define DELETED				-1
#define	MANCALA				0
#define SLOT_PLAYER			1
#define SLOT_OPPONENT		2
#define EQUAL				3
#define NOT					4
#define AND					5
#define OR					6
#define ADD					7
#define SUBTRACT			8
#define MULTIPLY			9
#define DIVIDE				10
#define GREATER_THAN		11
#define LESS_THAN			12
#define NUM_FUNCTION		13

#define POOLSIZE			600
#define MAX_ARGS			2
#define MAX_PROGRAM			4000
#define MAX_CONSTANT		7
#define BEGIN_DEPTH			6
#define NUMGENERATIONS      20

#define READY				0
#define DARWIN				1
#define FIT					2

short rand_from_pool();
short rand_node(int i);
short rand_mancala_function();

#endif

