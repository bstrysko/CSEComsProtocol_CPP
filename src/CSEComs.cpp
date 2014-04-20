#include <CSEComs.h>

CSEComs::CSEComs(string hostname)
{
	this->numCellsDetected = 0;
	this->numCellsDefect = 0;

	memset(grid, UNEXPLORED, CSE_GRID_NUM_CELLS);

	client = CSEComsClient(hostname);

	started = false;
}

CSEComs::~CSEComs()
{
}

bool CSEComs::isStarted()
{
	if(started)
	{
		return true;
	}
	else
	{
		uint8_t id;

		if(server.isTriggerReceived(&id))
		{
			client.sendAcknowledge(id);
			started = true;
		}

		return started;
	}
}

void CSEComs::detectCell(CSECellCoordinate c, CSECellStatus status)
{
	uint8_t row = c.first;
	uint8_t col = c.second;

	if((row >= CSE_GRID_NUM_CELLS_PER_COL)
		|| (col >= CSE_GRID_NUM_CELLS_PER_ROW))
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
	if(grid[row][col] == UNEXPLORED)
	{
		numCellsDetected++;
	}

	// Now see defect and previously not a defect
	if((status == DEFECT) && (grid[row][col] != DEFECT))
	{
		numCellsDefect++;
	}
	// Now see non-defect and previously a defect
	else if((status == NON_DEFECT) && (grid[row][col] == DEFECT))
	{
		numCellsDefect--;
	}

	grid[row][col] = status;
}

void CSEComs::flush()
{
	client.sendGridState(numCellsDetected, numCellsDefect, grid);
}

ostream& operator<<(ostream& os, const CSEComs& rhs)
{
	os << "[Num Cells Detected: " << (size_t)rhs.numCellsDetected << ",";
	os << " Num Cells Defect: " << (size_t)rhs.numCellsDefect << "]" << endl;
	os << "[Cell Status: " << endl;

	os << "\t    ";
	
	for(uint8_t i = 0; i < CSE_GRID_NUM_CELLS_PER_ROW; i++)
	{
		os << (int)i << " ";
	}
	
	os << endl << "\t    ";

	for(uint8_t i = 0; i < CSE_GRID_NUM_CELLS_PER_ROW; i++)
	{
		os << "--";
	}

	os << endl;
	
	for(uint8_t y = 0; y < CSE_GRID_NUM_CELLS_PER_COL; y++)
	{
		os << "\t" << (int)y << " | ";

		for(uint8_t x = 0; x < CSE_GRID_NUM_CELLS_PER_ROW; x++)
		{
			CSECellStatus cellStatus = (CSECellStatus)rhs.grid[y][x];
			
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
	return os;
}

