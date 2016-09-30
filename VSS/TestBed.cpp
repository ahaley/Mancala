#include "TestBed.h"

// performs a test run between two Player
void TestBed::Run_Test()
{
	Player *player1 = new Player(true, HUMAN);
	Player *player2 = new Player(false, INFORMED);

	MHP mprogram;
	Mancala mancala;
	Translater translater;
	PlayingField playingfield;

	clock_t start, finish;

	// load the MHS from MHS.txt
	string mhs = Load_MHS("MHS.txt");

	cout << "loaded string " << mhs << endl;

	// create an MHP from the MHS
	translater.Translate_MHS(mhs.c_str(), &mprogram);

	player2->install_MHP(&mprogram);
	
	srand((unsigned int)time(NULL));

	start = clock();
	
	playingfield.Play_Game(player1, player2);
	
	finish = clock();

	cout << "Match took " << (finish - start) / (double)CLOCKS_PER_SEC << " seconds.\n";
}


// Load_MHS loads an MHS from the file specified by filename
string TestBed::Load_MHS(const char *filename)
{
	ifstream fin(filename);

	if (!fin)
	{
		return "";
	}

	string rMHS; // used to store the MHS
	string token;

	while (fin >> token) 
	{
		rMHS += token + " ";
	}

	fin.close();
	return rMHS;
}

