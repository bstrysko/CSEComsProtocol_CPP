#ifndef _CSE_COMS_PROTOCOL_CSE_COMS_CLIENT_H_
#define _CSE_COMS_PROTOCOL_CSE_COMS_CLIENT_H_

#include <iostream>
#include <sstream>
#include <utility>

#include <stdint.h>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

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
    int socket_fd;
    struct sockaddr_in server_address;
    
    uint8_t numCellsDetected;
    uint8_t numCellsDefect;
    uint8_t cellStatus[CSE_COMS_CLIENT_NUM_CELLS_PER_ROW][CSE_COMS_CLIENT_NUM_CELLS_PER_COL];
  public:
    CSEComsClient(string hostname, uint32_t port);
    ~CSEComsClient();

    void detectCell(CSECellCoordinate c, CSECellStatus status);

    void flush();

    friend ostream& operator<<(ostream& os, const CSEComsClient& rhs);
};

#endif
