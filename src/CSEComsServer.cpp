#include <CSEComsServer.h>
#include <Shared.h>

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define SERVER_BUFFER_SIZE 3

void* serverThread(void* context);

CSEComsServer::CSEComsServer()
{
	triggerReceived = false;

	struct sockaddr_in address;
    socketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if(socketFd == -1)
	{
		throw ios_base::failure("Cannot create server socket");
	}

	fcntl(socketFd, F_SETFL, O_NONBLOCK);

	int optVal = 1;
	setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optVal, sizeof(int));

    bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
    address.sin_port = htons(CSE_COMS_SHARED_PORT);
    address.sin_addr.s_addr = htonl(INADDR_ANY);
     
    if(bind(socketFd, (struct sockaddr*)&address, sizeof(address)) == -1)
	{
		stringstream s;
		s << "Cannot bind server socket";
		s << "(erno: ";
		s << errno;
		s << ")";
		throw ios_base::failure(s.str());
	}
}

CSEComsServer::~CSEComsServer()
{
	close(socketFd);
}

void CSEComsServer::checkForTriggerPacket()
{
	uint8_t buffer[SERVER_BUFFER_SIZE];
    struct sockaddr_in clientAddress;
	socklen_t clientAddressSize = sizeof(clientAddress);

	if((recvfrom(
		socketFd, buffer, 
		SERVER_BUFFER_SIZE, 0,
		(struct sockaddr*)&clientAddress, &clientAddressSize) 
		== -1))
	{
		if(errno != EWOULDBLOCK)
		{
			stringstream s;
			s << "Error recvfrom ( ";
			s << strerror(errno);
			s << " )";
			throw ios_base::failure(s.str());
		}
	}
	else
	{
		if(buffer[0] != 0xFF)
		{
			throw ios_base::failure("Error 1st byte of Trigger Packet not 0xFF");
		}
		else if(buffer[2] != 1)
		{
			throw ios_base::failure("Error 3rd byte of Trigger Packet not 0x1");
		}
 
		triggerReceived = true;
		id = buffer[1];
	}
}

bool CSEComsServer::isTriggerReceived(uint8_t* idP)
{
	if(!triggerReceived)
	{
		checkForTriggerPacket();
	}

	if(triggerReceived)
	{
		(*idP) = id;
	}
	
	return triggerReceived;
}

