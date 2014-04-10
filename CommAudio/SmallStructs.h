#ifndef SMALLSTRUCTS_H
#define SMALLSTRUCTS_H


#include "bass.h"
#include "Master.h"

typedef struct {
	OVERLAPPED   overlapped; // overlapped MUST be the first entry for the completion routine to work
	SOCKET		   workSock;
	CHAR			 * buffer;
	WSABUF		 * dataBuf;
	WSAEVENT	 * wsaEvent;
	World * world;
} SocketInformation;

typedef struct {
	OVERLAPPED   overlapped; // overlapped MUST be the first entry for the completion routine to work
	SOCKET		   workSock;
	CHAR			 * buffer;
	WSABUF		 * dataBuf;
	WSAEVENT	 * wsaEvent;
	SOCKADDR_IN* dstAddr;
	INT		     dstAddrLen;
	CHAR fileName[MAXBUFLEN];
	HSTREAM streamHandle;
} MulticastSocketInformation;
#endif