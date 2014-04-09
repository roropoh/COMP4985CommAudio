#include "Master.h"


#include <stdio.h>


void CALLBACK doRecvMulticastWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags);
VOID CALLBACK doSendMulticastWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags);
DWORD WINAPI sendSessionToClient(LPVOID pVoid);



DWORD WINAPI sendMulticast(LPVOID pVoid)
{
	World* world = (World*)pVoid;

	SOCKADDR_IN *dstAddr = &world->sockMulti.dstAddr;
	INT						   len = world->sockMulti.dstAddrLen;

	MulticastSocketInformation msi;
	msi.overlapped = world->sockMulti.overlapped;
	msi.wsaEvent = &world->sockMulti.wsaEvent;
	msi.dataBuf = world->buffs.dataBuf;
	msi.buffer = world->buffs.buffer;
	msi.workSock = world->sockMulti.workSock;
	msi.dstAddr = dstAddr;
	msi.dstAddrLen = len;

	DWORD sentBytes = 0;
	DWORD flags = 0;

	strcpy(msi.buffer, "0. HOHO This is a packet 1024 bits long.");

	while (TRUE) {

		if (WSASendTo((msi.workSock), msi.dataBuf, 1, &sentBytes, flags, (SOCKADDR*)dstAddr, len, &msi.overlapped, doSendMulticastWork) == SOCKET_ERROR)
		if (GetLastError() != WSA_IO_PENDING) {
			//closeSendEverything(&sinf, "Socket error");
			int err = GetLastError();
			return FALSE;
		}

		if (waitForWSAEventToComplete(msi.wsaEvent) == FALSE)
			return FALSE;
	}

	// close everything
	return TRUE;
}



void CALLBACK doSendMulticastWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags)
{
	MulticastSocketInformation * msi = (MulticastSocketInformation*)overlapped;

	DWORD sentBytes = 0;
	DWORD flags = 0;

	int i = 0;
	sprintf(msi->buffer, "%d. HOHO THIS IS A PACKET", i);
	//si -> bytesSent += bytesTransferred;

	if (error != 0 || bytesTransferred == 0)
	{
		//closeSendEverything( sinf, 0);
		return;
	}


	if (WSASendTo((msi->workSock), msi->dataBuf, 1, &sentBytes, flags, (SOCKADDR*)msi->dstAddr, msi->dstAddrLen, &msi->overlapped, doSendMulticastWork) == SOCKET_ERROR)	{
		if (GetLastError() != WSA_IO_PENDING)
		{
			//closeRecvEverything(sinf, "Socket error");
			return;
		}
	}

	return;
}



DWORD WINAPI recvMulticast(LPVOID pVoid) {

	MulticastSocketInformation *msi = (MulticastSocketInformation *)pVoid;

	DWORD recvBytes = 0;
	DWORD flags = 0;

	while (TRUE)
	{
		if (WSARecvFrom(msi->workSock, msi->dataBuf, 1, &recvBytes, &flags, (SOCKADDR*)msi->dstAddr, &msi->dstAddrLen, &msi->overlapped, doRecvMulticastWork) == SOCKET_ERROR)
		{
			if (GetLastError() != WSA_IO_PENDING)
			{
				//closeRecvEverything(&sinf, "Socket error");
				return FALSE;
			}
		}

		if (waitForWSAEventToComplete(msi->wsaEvent) == FALSE) return FALSE;
	}
	return 0;
}



VOID CALLBACK doRecvMulticastWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags)
{
	MulticastSocketInformation *msi = (MulticastSocketInformation *)overlapped;

	DWORD bytesWrittenToFile = 0;
	DWORD recvBytes = 0;
	DWORD flags = 0;


	if (error != 0 || bytesTransferred == 0)
	{

		//closeRecvEverything(sinf, 0);
		return;
	}


	if (WSARecvFrom(msi->workSock, msi->dataBuf, 1, &recvBytes, &flags, (SOCKADDR*)msi->dstAddr, &msi->dstAddrLen, &msi->overlapped, doRecvMulticastWork) == SOCKET_ERROR)
	{
		if (GetLastError() != WSA_IO_PENDING)
		{
			//closeRecvEverything(sinf, "Socket error");
			return;
		}
	}

	return;
}



INT createServerBoundMulticastSocket(MulticastComponent* mSock)
{
	INT    optval = FALSE;
	ULONG	 TTL = 2;
	USHORT Interval = 30;


	SOCKADDR_IN *plclAddr = &(mSock->lclAddr); // SOCKADDR_IN
	SOCKADDR_IN *pdstAddr = &(mSock->dstAddr); // SOCKADDR_IN
	IP_MREQ			*pipMreq = &(mSock->ipMreq);  // IP_MREQ

	memset((PCHAR)plclAddr, 0, sizeof(SOCKADDR_IN));
	memset((PCHAR)pipMreq, 0, sizeof(IP_MREQ));

	if ((mSock->workSock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		// handle error
		return FALSE;
	}


	plclAddr->sin_family = AF_INET;
	plclAddr->sin_addr.s_addr = htonl(INADDR_ANY);
	plclAddr->sin_port = 0;

	pdstAddr->sin_family = AF_INET;
	pdstAddr->sin_addr.s_addr = inet_addr(mSock->ip);
	pdstAddr->sin_port = htons(mSock->portNumber);

	pipMreq->imr_multiaddr.s_addr = inet_addr(mSock->ip);
	pipMreq->imr_interface.s_addr = INADDR_ANY;


	mSock->dstAddrLen = sizeof(*pdstAddr);	// inAddr length


	if (bind(mSock->workSock, (SOCKADDR*)plclAddr, sizeof(*plclAddr)) == SOCKET_ERROR) {
		// handle error
		return FALSE;
	}


	if (setsockopt(mSock->workSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (PCHAR)pipMreq, sizeof(*pipMreq))) {
		int err = GetLastError();
		return FALSE;
	}

	if (setsockopt(mSock->workSock, IPPROTO_IP, IP_MULTICAST_TTL, (PCHAR)&TTL, sizeof(TTL))) {
		// handle error
		return FALSE;
	}


	if (setsockopt(mSock->workSock, IPPROTO_IP, IP_MULTICAST_LOOP, (PCHAR)&optval, sizeof(optval))) {
		// handle error
		return FALSE;
	}

	return TRUE;
}


INT createClientBoundMulticastSocket(MulticastComponent* mSock)
{
	INT optval = TRUE;

	SOCKADDR_IN *plclAddr = &(mSock->lclAddr); // SOCKADDR_IN
	IP_MREQ     *pipMreq = &(mSock->ipMreq);  // IP_MREQ

	mSock->workSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (setsockopt(mSock->workSock, SOL_SOCKET, SO_REUSEADDR, (CHAR*)&optval, sizeof(optval))) {
		// handle error
		return FALSE;
	}

	plclAddr->sin_family = AF_INET;
	plclAddr->sin_addr.s_addr = htonl(INADDR_ANY);
	plclAddr->sin_port = htons(mSock->portNumber);

	if (bind(mSock->workSock, (SOCKADDR*)plclAddr, sizeof(*plclAddr))) {
		// handle error
		return FALSE;
	}


	pipMreq->imr_multiaddr.s_addr = inet_addr(mSock->ip);
	pipMreq->imr_interface.s_addr = INADDR_ANY;

	if (setsockopt(mSock->workSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (CHAR*)pipMreq, sizeof(*pipMreq))) {
		// handle error
		int err = GetLastError();
		return FALSE;
	}

	return TRUE;
}