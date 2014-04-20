#ifndef _CSE_COMS_PROTOCOL_CSE_COMS_CLIENT_H_
#define _CSE_COMS_PROTOCOL_CSE_COMS_CLIENT_H_

#include <iostream>
#include <sstream>
#include <string>

#include <stdint.h>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "CSEGrid.h"

using namespace std;

class CSEComsClient
{
  private:
    int socketFd;
    struct sockaddr_in serverAddress;

    void send(uint8_t* buffer, size_t bufferSize);
  public:
    CSEComsClient();
    CSEComsClient(string hostname);
    ~CSEComsClient();

    void sendAcknowledge(uint8_t id);
    void sendGridState(uint8_t numCellsDetected, uint8_t numCellsDefect, CSEGrid grid);
};

#endif
