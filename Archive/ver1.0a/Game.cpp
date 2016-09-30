#include <iostream>
#include "GodProc.h"
#include "TestBed.h"

using namespace std;
class GodProc;

void main()
{
	if (GPMODE)
	{	
		GodProc godproc;
		godproc.GP();
	}
	else
	{
		TestBed testbed;	
		testbed.Run_Test();
	}
}