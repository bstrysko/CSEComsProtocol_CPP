#include <CSEComsClient.h>

CSEComsClient::CSEComsClient()
{
	this->numCellsDetected = 0;
	this->numCellsDefect = 0;

	memset(cellStatus, UNEXPLORED, CSE_COMS_CLIENT_NUM_CELLS);

	//TODO: open port
}

CSEComsClient::~CSEComsClient()
{
	//TODO: close port
}

void CSEComsClient::detectCell(CSECellCoordinate c, CSECellStatus status)
{
	uint8_t row = c.first;
	uint8_t col = c.second;
	uint8_t statusByte = (uint8_t)status;
	cellStatus[row][col] = statusByte;
}

void CSEComsClient::flush()
{
	//TODO:
}

ostream& operator<<(ostream& os, const CSEComsClient& rhs)
{
	os << "[Num Cells Detected: " << (size_t)rhs.numCellsDetected << ",";
	os << " Num Cells Defect: " << (size_t)rhs.numCellsDefect << "]" << endl;
	os << "[Cell Status: " << endl;
	
	for(uint8_t y = 0; y < CSE_COMS_CLIENT_NUM_CELLS_PER_COL; y++)
	{
		os << "\t";

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

