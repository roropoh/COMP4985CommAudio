#ifndef SMALLSTRUCTS_H
#define SMALLSTRUCTS_H

#include "GlobalShared.h"

typedef struct {
	OVERLAPPED * overlapped; // overlapped MUST be the first entry for the completion routine to work
	WSABUF		 * dataBuf;
	CHAR			 * buffer;
	SOCKET		   workSock;
	WSAEVENT	 * wsaEvent;
} SocketInformation;

typedef struct {
	OVERLAPPED * overlapped; // overlapped MUST be the first entry for the completion routine to work
	WSABUF		 * dataBuf;
	CHAR			 * buffer;
	SOCKET		   workSock;
	WSAEVENT	 * wsaEvent;
	SOCKADDR_IN* dstAddr;
	INT				   dstAddrLen;
} MulticastSocketInformation;

#endif