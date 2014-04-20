#include <CSEComsClient.h>
#include <Shared.h>

#define SEND_ACKNOWLEDGE_BUFFER_SIZE 2
#define SEND_GRID_BUFFER_SIZE \
	(2 + CSE_GRID_NUM_CELLS + 1)

CSEComsClient::CSEComsClient() : CSEComsClient::CSEComsClient("127.0.0.1")
{
}

CSEComsClient::CSEComsClient(string hostname)
{
	socketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if(socketFd == -1)
	{
		throw ios_base::failure("Error creating UDP socket");
	}

	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(CSE_COMS_SHARED_PORT);

    if(!inet_aton(hostname.c_str(), &serverAddress.sin_addr)) 
	{
		throw ios_base::failure("inet_aton error");
	}
}

CSEComsClient::~CSEComsClient()
{
	close(socketFd);
}

void CSEComsClient::send(uint8_t* buffer, size_t bufferSize)
{
	if(sendto(
		socketFd, buffer, bufferSize,
		0, (struct sockaddr *)&serverAddress, sizeof(serverAddress)
	) == -1)
	{
		throw ios_base::failure("sendto failed");
	}
}

void CSEComsClient::sendAcknowledge(uint8_t id)
{
	uint8_t buffer[SEND_ACKNOWLEDGE_BUFFER_SIZE];
	buffer[0] = id;
	buffer[1] = 1;

	send(buffer, SEND_ACKNOWLEDGE_BUFFER_SIZE);
}

void CSEComsClient::sendGridState(uint8_t numCellsDetected, uint8_t numCellsDefect, CSEGrid grid)
{
	uint8_t buffer[SEND_GRID_BUFFER_SIZE];
	buffer[0] = numCellsDetected;
	buffer[1] = numCellsDefect;
	
	memcpy(&buffer[2], grid, CSE_GRID_NUM_CELLS);

	buffer[SEND_GRID_BUFFER_SIZE-1] = -1;

	send(buffer, SEND_GRID_BUFFER_SIZE);
}
