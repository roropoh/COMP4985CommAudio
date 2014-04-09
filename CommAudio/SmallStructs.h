#ifndef SMALLSTRUCTS_H
#define SMALLSTRUCTS_H

#include "Master.h"

typedef struct {
	OVERLAPPED   overlapped; // overlapped MUST be the first entry for the completion routine to work
	SOCKET		   workSock;
	CHAR			 * buffer;
	WSABUF		 * dataBuf;
	WSAEVENT	 * wsaEvent;
} SocketInformation;

typedef struct {
	OVERLAPPED   overlapped; // overlapped MUST be the first entry for the completion routine to work
	SOCKET		   workSock;
	CHAR			 * buffer;
	WSABUF		 * dataBuf;
	WSAEVENT	 * wsaEvent;
	SOCKADDR_IN* dstAddr;
	INT		     dstAddrLen;
	MulticastComponent *sockMulti;
} MulticastSocketInformation;
#endif