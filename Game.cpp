#include <iostream>
#include "GodProc.h"
#include "TestBed.h"

using namespace std;
class GodProc;

void main()
{
	if (GPMODE)
	{	
		GodProc *godproc = NULL;
		try
		{
			godproc = new GodProc();
		}
		catch (...)
		{
			cerr << "Could not allocate the necesery space." << endl; 
		}

		godproc->GP();

	}
	else
	{
		TestBed testbed;	
		testbed.Run_Test();
	}
}

