#include "Master.h"

#include <stdio.h>


void CALLBACK doRecvMulticastWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags);
VOID CALLBACK doSendMulticastWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags);
DWORD WINAPI sendSessionToClient(LPVOID pVoid);

HSTREAM stream;

DWORD WINAPI sendMulticast(LPVOID pVoid)
{
	World* world = (World*)pVoid;

	SOCKADDR_IN *dstAddr = &world->sockMulti.dstAddr;
	INT						   len = world->sockMulti.dstAddrLen;

	MulticastSocketInformation msi;
	msi.overlapped = world->sockMulti.overlapped;
	msi.wsaEvent = &world->sockMulti.wsaEvent;
	msi.workSock = world->sockMulti.workSock;
	msi.dstAddr = dstAddr;
	msi.dstAddrLen = len;
	msi.dataBuf = world->buffs.dataBuf;
	msi.buffer = world->buffs.buffer;

	strcpy(msi.fileName, world->media.fileName);


	int error = initBass(&msi.streamHandle, "E:\\Dropbox\\2014 BCIT Winter\\COMP 4985 DataComm Option\\Assignment 4 (Final Project)\\COMP4985CommAudio\\CommAudio\\ladygaga.mp3");
	

	DWORD sentBytes = 0;
	DWORD flags = 0;



	error = ripSongPacket(&msi.streamHandle, msi.buffer);


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


	//si -> bytesSent += bytesTransferred;

	if (error != 0 || bytesTransferred == 0)
	{
		//closeSendEverything( sinf, 0);
		return;
	}

	error = ripSongPacket(&msi->streamHandle, msi->buffer);

	if (WSASendTo((msi->workSock), msi->dataBuf, 1, &sentBytes, flags, (SOCKADDR*)msi->dstAddr, msi->dstAddrLen, &msi->overlapped, doSendMulticastWork) == SOCKET_ERROR)	{
		if (GetLastError() != WSA_IO_PENDING)
		{
			//closeRecvEverything(sinf, "Socket error");
			return;
		}
	}

	return;
}



DWORD WINAPI recvMulticast(LPVOID pVoid) 
{
	SocketInformation* si = (SocketInformation*)pVoid;
	World* world = si->world;
	si->buffer = world->buffs.buffer;
	si->dataBuf = world->buffs.dataBuf;
	
	DWORD recvBytes = 0;
	DWORD flags = 0;


	if (!initMulticastComponent(&world->sockMulti, createClientBoundMulticastSocket))
		return FALSE;


	int error = initBass(&stream);


	while (TRUE)
	{
		if (WSARecvFrom(world->sockMulti.workSock, si->dataBuf, 1, &recvBytes, &flags, (SOCKADDR*)&world->sockMulti.lclAddr, &world->sockMulti.lclAddrLen, &si->overlapped, doRecvMulticastWork) == SOCKET_ERROR)
		{
			if (GetLastError() != WSA_IO_PENDING)
			{
				int error = GetLastError();//closeRecvEverything(&sinf, "Socket error");
				return FALSE;
			}
		}

		if (waitForWSAEventToComplete(&world->sockMulti.wsaEvent) == FALSE) return FALSE;
	}
	return 0;
}



VOID CALLBACK doRecvMulticastWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags)
{
	SocketInformation *si = (SocketInformation*)overlapped;
	World *world = si->world;

	DWORD recvBytes = 0;
	DWORD flags = 0;


	if (error != 0 || bytesTransferred == 0)
	{
		//closeRecvEverything(sinf, 0);
		return;
	}

	int err = playSongPacket(&stream, si->buffer);

	if (WSARecvFrom(world->sockMulti.workSock, si->dataBuf, 1, &recvBytes, &flags, (SOCKADDR*)&world->sockMulti.lclAddr, &world->sockMulti.lclAddrLen, &si->overlapped, doRecvMulticastWork) == SOCKET_ERROR)
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
	USHORT Interval = 30;


	SOCKADDR_IN *plclAddr = &(mSock->lclAddr); // SOCKADDR_IN
	SOCKADDR_IN *pdstAddr = &(mSock->dstAddr); // SOCKADDR_IN
	IP_MREQ			*pipMreq = &(mSock->ipMreq);  // IP_MREQ

	mSock->TTL = 2;

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
	pdstAddr->sin_port = htons(8191);

	pipMreq->imr_multiaddr.s_addr = inet_addr(mSock->ip);
	pipMreq->imr_interface.s_addr = INADDR_ANY;


	mSock->dstAddrLen = sizeof(*pdstAddr);	// inAddr length


	if (bind(mSock->workSock, (SOCKADDR*)plclAddr, sizeof(*plclAddr)) == SOCKET_ERROR) {
		// handle error
		int err = GetLastError();
		return FALSE;
	}


	if (setsockopt(mSock->workSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (PCHAR)pipMreq, sizeof(*pipMreq))) {
		int err = GetLastError();
		return FALSE;
	}

	if (setsockopt(mSock->workSock, IPPROTO_IP, IP_MULTICAST_TTL, (PCHAR)&mSock->TTL, sizeof(mSock->TTL))) {
		// handle error
		int err = GetLastError();
		return FALSE;
	}


	if (setsockopt(mSock->workSock, IPPROTO_IP, IP_MULTICAST_LOOP, (PCHAR)&optval, sizeof(optval))) {
		// handle error
		int err = GetLastError();
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
	plclAddr->sin_port = htons(8191);

	mSock->lclAddrLen = sizeof(*plclAddr);

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