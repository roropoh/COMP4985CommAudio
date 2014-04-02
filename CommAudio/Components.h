#ifndef STRUCTS_H
#define STRUCTS_H

#include "GlobalShared.h"

typedef struct {
	OVERLAPPED	overlapped;
	WSAEVENT		wsaEvent;
	SOCKET			workSock;
	SOCKADDR_IN	inAddr;
	IP_MREQ			ipMreq;
	ULONG				TTL;
	USHORT			Interval;
	INT					inAddrLen;
	INT					protocol;
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
	INT					protocol;
	INT					portNumber;
	CHAR				ip[MAXBUFLEN];
} SocketsComponent;


typedef struct {
	WSABUF dataBuf;
	CHAR*  buffer;
	INT		 packetSize;
} BuffersComponent;


typedef struct {
	DWORD bytesSent;
	DWORD bytesReceived;
	INT		firstTimestamp;
	INT		lastTimestamp;
	INT		numPackets;
	DWORD packetSize;
} StatsComponent;


typedef struct {

} MediaComponent;


typedef struct {
	SocketsComponent sockTcp;
	MulticastComponent sockUdp;
	BuffersComponent buffs;
	StatsComponent	 stats;
	MediaComponent	 media;
	int clientOrServer;
} World;

#endif