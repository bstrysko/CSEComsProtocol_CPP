#ifndef _CSE_COMS_PROTOCOL_CSE_COMS_CLIENT_H_
#define _CSE_COMS_PROTOCOL_CSE_COMS_CLIENT_H_

#include <iostream>
#include <utility>

#include <stdint.h>
#include <cstring>

using namespace std;

#define CSE_COMS_CLIENT_NUM_CELLS_PER_ROW 9
#define CSE_COMS_CLIENT_NUM_CELLS_PER_COL 9
#define CSE_COMS_CLIENT_NUM_CELLS \
  (CSE_COMS_CLIENT_NUM_CELLS_PER_ROW * \
   CSE_COMS_CLIENT_NUM_CELLS_PER_COL)

typedef pair<uint8_t, uint8_t> CSECellCoordinate;

enum CSECellStatus
{
  NON_DEFECT = 0,
  DEFECT = 1,
  UNEXPLORED = 2
};

class CSEComsClient
{
  private:
    uint8_t numCellsDetected;
    uint8_t numCellsDefect;
    uint8_t cellStatus[CSE_COMS_CLIENT_NUM_CELLS_PER_ROW][CSE_COMS_CLIENT_NUM_CELLS_PER_COL];
  public:
    CSEComsClient();
    ~CSEComsClient();

    void detectCell(CSECellCoordinate c, CSECellStatus status);

    void flush();

    friend ostream& operator<<(ostream& os, const CSEComsClient& rhs);
};

#endif
