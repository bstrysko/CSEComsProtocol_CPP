#include <iostream>
#include <sstream>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include <CSEComsProtocol/CSEComsClient.h>

using namespace std;

void usage(string name);
int stringToInt(char* s);

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		usage(argv[0]);
		return 1;
	}

	string hostname = argv[1];
	int port = stringToInt(argv[2]);	

	CSEComsClient client(hostname, port);

	cout << client << endl;
	client.detectCell(CSECellCoordinate(0,0), DEFECT);
	cout << client << endl;
	client.detectCell(CSECellCoordinate(0,1), NON_DEFECT);
	cout << client << endl;
	client.detectCell(CSECellCoordinate(8,8), NON_DEFECT);
	cout << client << endl;	
	client.detectCell(CSECellCoordinate(8,8), DEFECT);
	cout << client << endl;
	client.detectCell(CSECellCoordinate(3,3), DEFECT);
	cout << client << endl;
	client.detectCell(CSECellCoordinate(8,8), NON_DEFECT);
	cout << client << endl;

	client.flush();

	return 0;
}

void usage(string name)
{
	cout << "usage: ./" << name << " [hostname] [port]" << endl;
}

int stringToInt(char* s)
{
	int result;
	
	result = atoi(s);
	
	if(result == 0 && s[0] != '0')
	{
		stringstream o;
		o << s << " is not a number";		
		throw ios_base::failure(o.str());
	}

	return result;
}
