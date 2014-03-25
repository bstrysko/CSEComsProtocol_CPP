#include <CSEComsClient.h>

#define CSE_COMS_CLIENT_BUFFER_SIZE \
	(2 + CSE_COMS_CLIENT_NUM_CELLS + 1)

CSEComsClient::CSEComsClient(string hostname, uint32_t port)
{
	this->numCellsDetected = 0;
	this->numCellsDefect = 0;

	memset(cellStatus, UNEXPLORED, CSE_COMS_CLIENT_NUM_CELLS);

	socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if(socket_fd == -1)
	{
		throw ios_base::failure("Error creating UDP socket");
	}

	bzero(&server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);

    if(!inet_aton(hostname.c_str(), &server_address.sin_addr)) 
	{
		throw ios_base::failure("inet_aton error");
	}
}

CSEComsClient::~CSEComsClient()
{
	close(socket_fd);
}

void CSEComsClient::detectCell(CSECellCoordinate c, CSECellStatus status)
{
	uint8_t row = c.first;
	uint8_t col = c.second;

	if((row >= CSE_COMS_CLIENT_NUM_CELLS_PER_COL)
		|| (col >= CSE_COMS_CLIENT_NUM_CELLS_PER_ROW))
	{
		stringstream o;
		o << "CSECellCoordinate ";
		o << "(" << (int)c.first << ", " << (int)c.second << ")";
		o << " is invalid";
		throw ios_base::failure(o.str());
	}

	if(status == UNEXPLORED)
	{
		throw ios_base::failure("Cannot unexplore a cell");
	}

	// Not a re-pass
	if(cellStatus[row][col] == UNEXPLORED)
	{
		numCellsDetected++;

		if(status == DEFECT)
		{
			numCellsDefect++;
		}
	}

	uint8_t statusByte = (uint8_t)status;
	cellStatus[row][col] = statusByte;
}

void CSEComsClient::flush()
{
	uint8_t buffer[CSE_COMS_CLIENT_BUFFER_SIZE];
	buffer[0] = numCellsDetected;
	buffer[1] = numCellsDefect;
	
	memcpy(&buffer[2], cellStatus, CSE_COMS_CLIENT_NUM_CELLS);

	buffer[CSE_COMS_CLIENT_BUFFER_SIZE-1] = -1;

	int r = sendto(socket_fd, buffer, CSE_COMS_CLIENT_BUFFER_SIZE, 0, (struct sockaddr *)&server_address,sizeof(server_address));

	if(r == -1)
	{
		throw ios_base::failure("sendto failed");
	}
}

ostream& operator<<(ostream& os, const CSEComsClient& rhs)
{
	os << "[Num Cells Detected: " << (size_t)rhs.numCellsDetected << ",";
	os << " Num Cells Defect: " << (size_t)rhs.numCellsDefect << "]" << endl;
	os << "[Cell Status: " << endl;

	os << "\t    ";
	
	for(uint8_t i = 0; i < CSE_COMS_CLIENT_NUM_CELLS_PER_ROW; i++)
	{
		os << (int)i << " ";
	}
	
	os << endl << "\t    ";

	for(uint8_t i = 0; i < CSE_COMS_CLIENT_NUM_CELLS_PER_ROW; i++)
	{
		os << "--";
	}

	os << endl;
	
	for(uint8_t y = 0; y < CSE_COMS_CLIENT_NUM_CELLS_PER_COL; y++)
	{
		os << "\t" << (int)y << " | ";

		for(uint8_t x = 0; x < CSE_COMS_CLIENT_NUM_CELLS_PER_ROW; x++)
		{
			CSECellStatus cellStatus = (CSECellStatus)rhs.cellStatus[y][x];
			
			char s;

			switch(cellStatus)
			{
				case NON_DEFECT:
				{
					s = ' ';
					break;
				}
				case DEFECT:
				{
					s = 'X';
					break;
				}
				default:
				{
					s = '?';
				}
			}

			os << s << " ";
		}
		
		os << endl;
	}

	os << "]" << endl;
}

