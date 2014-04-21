#ifndef _CSE_COMS_PROTOCOL_CSE_CELL_H_
#define _CSE_COMS_PROTOCOL_CSE_CELL_H_

#include <utility>

using namespace std;

typedef pair<uint8_t, uint8_t> CSECellCoordinate;

enum CSECellStatus : uint8_t
{
  NON_DEFECT = 0,
  DEFECT = 1,
  UNEXPLORED = 2
};

#endif
