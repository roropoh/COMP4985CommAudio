#include "Master.h"

INT createSendSocket(SocketsComponent* socks)
{
	SOCKADDR_IN* pinAddr = &(socks->inAddr);
	HOSTENT* hostent = gethostbyname(socks->ip);

	memset((PCHAR)pinAddr, 0, sizeof(SOCKADDR_IN));
	memcpy((PCHAR)&pinAddr->sin_addr, hostent->h_addr, hostent->h_length);

	pinAddr -> sin_family				= AF_INET;
	pinAddr -> sin_port					= htons(socks->portNumber);

	INT len = socks -> inAddrLen = sizeof(*pinAddr);	// inAddr length
	INT pro = socks -> protocol;											// protocol type

	if((socks->workSock = WSASocket(AF_INET, pro, 0, 0, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) {
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
-- INTERFACE:		void createBoundSocket(SocketsComponent* socks)
--
--							SocketsComponent* socks: struct containing socket initialization arguments.
--								
-- RETURNS:		INT. TRUE on success, FALSE on failure
--
-- NOTES:
--
-- Creates an asynchronous socket to listen for connections and binds it to a port.
----------------------------------------------------------------------------------------------------------------------*/
INT createBoundSocket(SocketsComponent* socks)
{
	SOCKADDR_IN *pinAddr = &(socks->inAddr); // SOCKADDR_IN

	memset((PCHAR)pinAddr, 0, sizeof(SOCKADDR_IN));

	pinAddr -> sin_family				= AF_INET;
	pinAddr -> sin_addr.s_addr	= htonl(INADDR_ANY);
	pinAddr -> sin_port					= htons(socks->portNumber);


	INT len = socks -> inAddrLen = sizeof(*pinAddr);	// inAddr length
	INT pro = socks -> protocol;											// protocol type


	if((socks->listenSock = WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) {
		// put error handling code here
		int err = GetLastError();
		return FALSE;
	}

	if(bind(socks->listenSock, (PSOCKADDR) pinAddr, len) == SOCKET_ERROR) {
		// put error handling code here
		int err = GetLastError();
		return FALSE;
	}
	return TRUE;
}


static void initBuffersComponent(BuffersComponent* buffs)
{
	buffs->packetSize		= PACKETSIZE; 
	buffs->buffer				= (CHAR*)calloc(buffs->packetSize, sizeof(CHAR));
	buffs->dataBuf.len	= buffs->packetSize;
	buffs->dataBuf.buf	= buffs->buffer;
}


static void initStatsComponent(StatsComponent* stats)
{
	// Init StatisticsComponent
	stats->bytesSent			= 0;
	stats->bytesReceived	= 0;
	stats->firstTimestamp = 0;
	stats->lastTimestamp  = 0;
	stats->packetSize			= PACKETSIZE;
	stats->numPackets			= 0;
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

	if(cos == SERVER) {
		if( ! initServer(&world->sockTcp, &world->sockUdp)) 
			return FALSE;
	}

	else if(cos == CLIENT) {
		if( ! initClient(&world->sockTcp, &world->sockUdp)) 
			return FALSE;
	}

	initBuffersComponent(&world->buffs);
	initStatsComponent  (&world->stats);

	return TRUE;
}
