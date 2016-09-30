#include "TestBed.h"

// performs a test run between two Player
void TestBed::Run_Test()
{
	Player *player1 = new Player(PLAYER1, HUMAN);
	Player *player2 = new Player(PLAYER2, INFORMED);

	MHP mprogram1;
//	MHP mprogram2;

	Mancala mancala;
	Translater translater;
	PlayingField playingfield;

	clock_t start, finish;

	// load the MHS from MHS.txt
	string mhs = Load_MHS("MHS.txt");

	// create an MHP from the MHS
	translater.Translate_MHS(mhs.c_str(), &mprogram1);

	//player1->install_MHP(&mprogram1);
	player2->install_MHP(&mprogram1);
	
	srand((unsigned int)time(NULL));

	start = clock();
	
	playingfield.Play_Game(player1, player2);
	
	finish = clock();

	cout << "Match took " << (finish - start) / (double)CLOCKS_PER_SEC << " seconds.\n";
}


// Load_MHS loads an MHS from the file specified by filename
string TestBed::Load_MHS(string filename)
{
	ifstream fin(filename.c_str());

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