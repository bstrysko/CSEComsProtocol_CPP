#include <iostream>
#include <sstream>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include <CSEComsProtocol/CSEComsClient.h>

using namespace std;

void usage(string name);
uint8_t stringToUInt8(char* s);

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		usage(argv[0]);
		return 1;
	}

	CSEComsClient client;

	cout << client << endl;

	client.detectCell(CSECellCoordinate(0,0), DEFECT);
	client.detectCell(CSECellCoordinate(0,1), NON_DEFECT);

	cout << client << endl;

	return 0;
}

void usage(string name)
{
	cout << "usage: " << name << "" << endl;
}

uint8_t stringToUInt8(char* s)
{
	uint8_t result;
	
	result = atoi(s);
	
	if(result == 0 && s[0] != '0')
	{
		stringstream o;
		o << s << " is not a number";		
		throw ios_base::failure(o.str());
	}

	return result;
}
