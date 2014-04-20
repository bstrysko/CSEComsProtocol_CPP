#ifndef _CSE_COMS_PROTOCOL_CSE_COMS_H_
#define _CSE_COMS_PROTOCOL_CSE_COMS_H_

#include <iostream>
#include <sstream>
#include <utility>

#include <stdint.h>
#include <cstring>

#include "CSEComsClient.h"
#include "CSEComsServer.h"

using namespace std;

class CSEComs
{
  private:
    uint8_t numCellsDetected;
    uint8_t numCellsDefect;
    CSEGrid grid;

    CSEComsClient client;
    CSEComsServer server;  

    bool started;
  public:
    CSEComs(string hostname);
    ~CSEComs();

    bool isStarted();
    void detectCell(CSECellCoordinate c, CSECellStatus status);
    void flush();

    friend ostream& operator<<(ostream& os, const CSEComs& rhs);
};

#endif
