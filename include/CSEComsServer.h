#ifndef _CSE_COMS_PROTOCOL_CSE_COMS_SERVER_H_
#define _CSE_COMS_PROTOCOL_CSE_COMS_SERVER_H_

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

class CSEComsServer
{
  private:
    int socketFd; 
    bool triggerReceived;
    uint8_t id;

    void checkForTriggerPacket();
  public:
    CSEComsServer();
    ~CSEComsServer();
  
    bool isTriggerReceived(uint8_t* idP);
};

#endif
