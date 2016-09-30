#include "GodProc.h"
#include "TestBed.h"
#include <ctime>


GodProc::GodProc()
{
    player_one = NULL;
    player_two = NULL;
    mancala = NULL;
}

GodProc::~GodProc()
{
	if (player_one != NULL)
	{
		delete player_one;
		player_one = NULL;
	}
	if (player_two != NULL)
	{
		delete player_two;
		player_two = NULL;
	}
	if (mancala != NULL)
	{
		delete mancala;
		mancala = NULL;
	}
}

// Fills the pool with randomly generated MHPs
void GodProc::Create_Random_Pool()
{	
	for (int i = 0; i < POOLSIZE; i++)
	{
		Create_Random_MHP(&pool[i], BEGIN_DEPTH);
		pool[i].state = READY;
	}
}

// Creates a randomly generated Mancala Heuristic Program (MHP)
short GodProc::Create_Random_MHP(MHP *mprogram, int depth_counter)
{
	if (depth_counter == 0)
	{
		return mprogram->Add_Node(rand() % MAX_CONSTANT);
	}

	short function = rand_mancala_function();
	short node = mprogram->Add_Node(function);

	if (node == -1)
	{
		cout << "MHP max length reached, aborting" << endl;
		exit(0);
	}

	switch(function)
	{
	// unary functions
	case MANCALA:
	case SLOT_PLAYER:
	case SLOT_OPPONENT:
	case NOT:
		mprogram->Point_Arg(0, node, Create_Random_MHP(mprogram, depth_counter - 1));

	// binary functions
	case EQUAL:
	case GREATER_THAN:
	case LESS_THAN:
	case AND:
	case OR:
	case ADD:
	case SUBTRACT:
	case MULTIPLY:
	case DIVIDE:
		mprogram->Point_Arg(0, node, Create_Random_MHP(mprogram, depth_counter - 1));
		mprogram->Point_Arg(1, node, Create_Random_MHP(mprogram, depth_counter - 1));
	}
	
	return node;
}

// The entire pool of random MHPs do battle with the Straw Man!!
void GodProc::Battle_Strawman()
{
	Player *straw_man = new Player(true, STRAWMAN);
	Player *player = new Player(false, INFORMED);

	PlayingField playingfield;
	
	double result;
	ofstream fout("winner.txt");

	clock_t start, finish;

	for (int i = 0; i < POOLSIZE; i++)
	{
		player->install_MHP(&pool[i]);

		start = clock();
		result = playingfield.Play_Game(straw_man, player);
		finish = clock();

		cout << "Result = " << result << " Time = " << (finish - start) / (double)CLOCKS_PER_SEC << " s" << endl;
		if (result < -20)
		{
			fout << "Result = " << result << endl;
			fout << translater.Translate_MHP(&pool[i], 0, 1) << "\n\n";
		}
	}

	fout.close();
};

void GodProc::GP()
{
	Player *player1;
	Player *player2;

	try
	{
		player1 = new Player(true, INFORMED);
		player2 = new Player(false, INFORMED);
	}
	catch (...)
	{
		cerr << "Could not create players." << endl;
	}

	PlayingField playingfield;
	
	double result;

	short random_1;
	short random_2;
	short random_kid_1;
	short random_kid_2;
	short random_node_1;
	short random_node_2;

	int evaluated = 0;

	bool done = false;

	MHP *sub_mhp1 = NULL;
	MHP *sub_mhp2 = NULL;

	srand(time(NULL));

	try
	{
		Create_Random_Pool();
	}
	catch (...)
	{
		cerr << "Could not create random pool." << endl;
	}

    clock_t start, finish;

    start = clock();



	for (int g = 0; g < NUMGENERATIONS; g++)
	{
		random_1 = 0;
		random_2 = POOLSIZE - 1;
		done = false;

		// fight
		evaluated = 0;
		while (!done)
		{
			// find a MHP that is ready
			do
			{
				random_1 = rand_from_pool();
			} while (pool[random_1].state != READY);

			// find another MHP that is ready and is not the one already chosen
			do
			{
				random_2 = rand_from_pool();
			} while (pool[random_2].state != READY || random_2 == random_1);

			evaluated += 2;
			if (evaluated >= POOLSIZE - 1)
				done = true;

			// install the chosen MHPs into the players
			player1->install_MHP(&pool[random_1]);
			player2->install_MHP(&pool[random_2]);
	
			result = playingfield.Play_Game(player1, player2);
	
			if (result > 0)
			{
				pool[random_1].state = FIT;
				pool[random_2].state = DARWIN;
			}
			else
			{
				pool[random_1].state = DARWIN;
				pool[random_2].state = FIT;
			}
		}

		done = false;
		random_1 = random_kid_1 = 0;
		random_2 = random_kid_2 = POOLSIZE - 1;

		// mate
		while (!done)
		{
			
            // find a fit MHP from the beginning of the pool
			while(pool[random_1].state != FIT)
			{
				random_1++;
				if (done = (random_1 > random_2))
					break;
			}

			if (done) break;

            // find a fit MHP from the end of the pool
			while (pool[random_2].state != FIT)
			{
				random_2--;
				if (done = (random_1 > random_2))
					break;
			}

			if (done) break;

            // find a Darwin'ed MHP from the beginning of the pool
			while (pool[random_kid_1].state != DARWIN)
			{
				random_kid_1++;
				if (done = (random_kid_1 > random_kid_2))
					break;
			}

			if (done) break;
		
		    // find a Darwin'ed MHP from the end of the pool
			while (pool[random_kid_2].state != DARWIN)
			{
				random_kid_2--;
				if (done = (random_kid_1 > random_kid_2))
					break;
			}

			if (done) break;
			
			sub_mhp1 = new MHP();
			sub_mhp2 = new MHP();	
			
			pool[random_kid_1].Remove_SubMHP(0, sub_mhp1);
			pool[random_kid_1].Add_SubMHP(0, &pool[random_1]);
			
			pool[random_kid_2].Remove_SubMHP(0, sub_mhp2);
			pool[random_kid_2].Add_SubMHP(0, &pool[random_2]);

			random_node_1 = rand_node(pool[random_kid_1].eop);
			random_node_2 = rand_node(pool[random_kid_2].eop);

			delete sub_mhp1;
			delete sub_mhp2;
			sub_mhp1 = new MHP();
			sub_mhp2 = new MHP();

			pool[random_kid_1].Remove_SubMHP(random_node_1, sub_mhp1);
			pool[random_kid_2].Remove_SubMHP(random_node_2, sub_mhp2);
			
			pool[random_kid_1].Add_SubMHP(0, sub_mhp2);
			pool[random_kid_2].Add_SubMHP(0, sub_mhp1);
			
			pool[random_1].state = READY;
			pool[random_2].state = READY;
			pool[random_kid_1].state = READY;
			pool[random_kid_2].state = READY;
			

			delete sub_mhp2;
			sub_mhp2 = NULL;
			delete sub_mhp1;
			sub_mhp1 = NULL;
		}

		// mutate
		for (random_1 = 0; random_1 < 10; random_1++)
		{
			random_2 = rand_from_pool();
			pool[random_2].Mutate();
		}

		for (random_1 = 0; random_1 < POOLSIZE; random_1++)
		{
			pool[random_1].state = READY;
		}


		Print_Report(g);
	}
    finish = clock();
    
    cout << "GP Total = " << (finish - start) / (double)CLOCKS_PER_SEC << endl;
	
}

void GodProc::Print_Report(int report_num)
{
	char filename[20];
	sprintf(filename, "output%d.txt", report_num);

	ofstream fout(filename);
	Translater translater;

	for (int z = 0; z < POOLSIZE; z++)
	{
		if (pool[z].state == READY)
		{
			fout << "THS number " << z << endl;
			fout << translater.Translate_MHP(&pool[z], 0, 1) << endl << endl;
		}
	}
	fout.close();
}

void GodProc::Test_Mechanics()
{

	Translater translater;
	MHP mhp1, mhp2;
	MHP sub_mhp1, sub_mhp2;

	ofstream fout("output.txt");

	translater.Translate_MHS("(ADD (ADD 1 1) (ADD 2 2))", &mhp1);
	translater.Translate_MHS("(ADD (ADD 1 1) (SUBTRACT 2 2))", &mhp2);
	/*
	fout << translater.Translate_MHP(&mhp1, 0) << endl;
	fout << "eop = " << mhp1.eop << endl;
	fout << translater.Translate_MHP(&mhp2, 0) << endl;
	fout << "eop = " << mhp2.eop << endl;
	fout << endl;
*/	


//	mhp1.Remove_SubMHP(4, &sub_mhp1);
//	mhp2.Remove_SubMHP(4, &sub_mhp2);

//	mhp1.Add_SubMHP(0, &sub_mhp2);
//	mhp1.Add_SubMHP(0, &sub_mhp2);
	

	
	fout << translater.Translate_MHP(&mhp1, 0, 1) << endl;
	fout << "eop = " << mhp1.eop << endl;
	fout << translater.Translate_MHP(&mhp2, 0, 1) << endl;
	fout << "eop = " << mhp2.eop << endl;


	fout.close();


}

