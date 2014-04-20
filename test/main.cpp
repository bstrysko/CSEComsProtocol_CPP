#include <iostream>
#include <sstream>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include <CSEComsProtocol/CSEComs.h>

using namespace std;

void usage(string name);

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		usage(argv[0]);
		return 1;
	}

	string hostname = argv[1];

	CSEComs coms(hostname);

	while(!coms.isStarted())
	{
		cout << "Waiting for start..." << endl;
		usleep(1000000);
	}

	cout << coms << endl;
	coms.detectCell(CSECellCoordinate(0,0), DEFECT);
	cout << coms << endl;
	coms.detectCell(CSECellCoordinate(0,1), NON_DEFECT);
	cout << coms << endl;
	coms.detectCell(CSECellCoordinate(8,8), NON_DEFECT);
	cout << coms << endl;	
	coms.detectCell(CSECellCoordinate(8,8), DEFECT);
	cout << coms << endl;
	coms.detectCell(CSECellCoordinate(3,3), DEFECT);
	cout << coms << endl;
	coms.detectCell(CSECellCoordinate(8,8), NON_DEFECT);
	cout << coms << endl;

	coms.flush();

	return 0;
}

void usage(string name)
{
	cout << "usage: ./" << name << " [hostname]" << endl;
}
