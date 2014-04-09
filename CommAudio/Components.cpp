#include "Master.h"

INT createSendSocket(UnicastComponent *sockSessn)
{
	SOCKADDR_IN* pinAddr = &(sockSessn->inAddr);
	HOSTENT* hostent = gethostbyname(sockSessn->ip);

	memset((PCHAR)pinAddr, 0, sizeof(SOCKADDR_IN));
	memcpy((PCHAR)&pinAddr->sin_addr, hostent->h_addr, hostent->h_length);

	pinAddr->sin_family = AF_INET;
	pinAddr->sin_port = htons(sockSessn->portNumber);

	INT len = sockSessn->inAddrLen = sizeof(*pinAddr);	// inAddr length

	if ((sockSessn->workSock = WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) {
		// put error handling code here
		int err = GetLastError();
		return FALSE;
	}
	return TRUE;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: createBoundSocket
--
-- DATE:				March 30th, 2014
--
-- REVISIONS:		None
--
-- DESIGNER:		Sam Youssef
-- PROGRAMMER:	Sam Youssef
--
-- INTERFACE:		void createBoundSocket(SocketsComponent* sockSessn)
--
--							SocketsComponent* sockSessn: struct containing socket initialization arguments.
--
-- RETURNS:		INT. TRUE on success, FALSE on failure
--
-- NOTES:
--
-- Creates an asynchronous socket to listen for connections and binds it to a port.
----------------------------------------------------------------------------------------------------------------------*/
INT createBoundSocket(UnicastComponent *sockSessn)
{
	SOCKADDR_IN *pinAddr = &(sockSessn->inAddr); // SOCKADDR_IN

	memset((PCHAR)pinAddr, 0, sizeof(SOCKADDR_IN));

	pinAddr->sin_family = AF_INET;
	pinAddr->sin_addr.s_addr = htonl(INADDR_ANY);
	pinAddr->sin_port = htons(sockSessn->portNumber);


	INT len = sockSessn->inAddrLen = sizeof(*pinAddr);	// inAddr length


	if ((sockSessn->listenSock = WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) {
		// put error handling code here
		int err = GetLastError();
		return FALSE;
	}

	if (bind(sockSessn->listenSock, (PSOCKADDR)pinAddr, len) == SOCKET_ERROR) {
		// put error handling code here
		int err = GetLastError();
		return FALSE;
	}
	return TRUE;
}

static INT initUnicastComponent(UnicastComponent* sockSessn, INT initHostType(UnicastComponent*))
{
	sockSessn->wsaEvent = WSACreateEvent();

	ZeroMemory(&sockSessn->overlapped, sizeof(WSAOVERLAPPED));

	return initHostType(sockSessn);
}

INT initMulticastComponent(MulticastComponent* sockMulti, INT createSocketType(MulticastComponent*))
{
	sockMulti->wsaEvent = WSACreateEvent();

	ZeroMemory(&sockMulti->overlapped, sizeof(WSAOVERLAPPED));

	return createSocketType(sockMulti);
}


static VOID initBuffersComponent(BuffersComponent* buffs)
{
	buffs->packetSize = PACKETSIZE;
	buffs->buffer = (CHAR*)calloc(buffs->packetSize, sizeof(CHAR));
	buffs->dataBuf = (WSABUF*)calloc(1, sizeof(WSABUF));
	buffs->dataBuf->len = buffs->packetSize;
	buffs->dataBuf->buf = buffs->buffer;
}


static VOID initStatsComponent(StatsComponent* stats)
{
	// Init StatisticsComponent
	stats->bytesSent = 0;
	stats->bytesReceived = 0;
	stats->firstTimestamp = 0;
	stats->lastTimestamp = 0;
	stats->packetSize = PACKETSIZE;
	stats->numPackets = 0;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: initWorld
--
-- DATE:		March 30th, 2014
--
-- REVISIONS:	None
--
-- DESIGNER:		Sam Youssef
-- PROGRAMMER:	Sam Youssef
--
-- INTERFACE:		void initWorld(World* world)
--
--							World* world: struct containing all the component structs that make up the program.
--
-- RETURNS:		void.
--
-- NOTES:
-- This function creates all the component structs the make up the program (stats, buffers, sockets and media).
----------------------------------------------------------------------------------------------------------------------*/
INT initWorld(World* world)
{
	int cos = world->clientOrServer;

	if (cos == SERVER) {
		if (!initUnicastComponent(&world->sockSessn, initServer))
			return FALSE;

		if (!initMulticastComponent(&world->sockMulti, createServerBoundMulticastSocket))
			return FALSE;
	}

	else if (cos == CLIENT) {
		if (!initUnicastComponent(&world->sockSessn, initClient))
			return FALSE;
	}


	initBuffersComponent(&world->buffs);
	//initStatsComponent  (&world->stats);

	return TRUE;
}


VOID cleanWorld(World* world)
{

}