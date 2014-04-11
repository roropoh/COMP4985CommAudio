#ifndef STRUCTS_H
#define STRUCTS_H

#include "GlobalShared.h"

typedef struct {
	OVERLAPPED	overlapped;
	WSAEVENT		wsaEvent;
	SOCKET			workSock;
	SOCKADDR_IN	lclAddr;
	SOCKADDR_IN dstAddr;
	IP_MREQ			ipMreq;
	ULONG				TTL;
	INT					dstAddrLen;
	INT					lclAddrLen;
	INT					portNumber;
	CHAR				ip[MAXBUFLEN];
} MulticastComponent;


typedef struct {
	OVERLAPPED	overlapped;
	WSAEVENT		wsaEvent;
	SOCKET			listenSock;
	SOCKET			workSock;
	SOCKADDR_IN	inAddr;
	INT					inAddrLen;
	INT					portNumber;
	CHAR				ip[MAXBUFLEN];
} UnicastComponent;


typedef struct {
	WSABUF* dataBuf;
	CHAR*   buffer;
	INT		  packetSize;
} BuffersComponent;


typedef struct {
	DWORD bytesSent;
	DWORD bytesReceived;
	INT		firstTimestamp;
	INT		lastTimestamp;
	INT		numPackets;
	DWORD packetSize;
	BOOL connected;
} StatsComponent;


typedef struct {
	CHAR fileName[MAXBUFLEN];
} MediaComponent;


typedef struct {
	UnicastComponent	 sockSessn;
	MulticastComponent sockMulti;
	BuffersComponent	 buffs;
	//StatsComponent	 stats;
	MediaComponent	 media;
	INT clientOrServer;
} World;

#endif