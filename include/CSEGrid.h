#ifndef _CSE_COMS_PROTOCOL_CSE_GRID_H_
#define _CSE_COMS_PROTOCOL_CSE_GRID_H_

#include "CSECell.h"

#define CSE_GRID_NUM_CELLS_PER_ROW 9
#define CSE_GRID_NUM_CELLS_PER_COL 9
#define CSE_GRID_NUM_CELLS \
  (CSE_GRID_NUM_CELLS_PER_ROW * \
   CSE_GRID_NUM_CELLS_PER_COL)

typedef CSECellStatus CSEGrid[CSE_GRID_NUM_CELLS_PER_ROW][CSE_GRID_NUM_CELLS_PER_COL];

#endif
