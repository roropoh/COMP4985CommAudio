#include "Master.h"

#include <stdio.h>


void CALLBACK doRecvMulticastWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags);
VOID CALLBACK doSendMulticastWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags);
DWORD WINAPI sendSessionToClient(LPVOID pVoid);

HSTREAM stream;
WSABUF dataBuf;

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
	msi.streamHandle = initBass(msi.fileName);
	strcpy(msi.fileName, world->media.fileName);

	DWORD sentBytes = 0;
	DWORD flags = 0;

	//WSABUF *dataBuf = (WSABUF*)calloc(1, sizeof(WSABUF));


	BASS_Init(-1, 44100, 0, 0, NULL);
	stream = BASS_StreamCreateFile(FALSE, "C:\\Users\\pc1\\Documents\\GitHub\\COMP4985CommAudio\\CommAudio\\ladygaga.mp3", 0, 0, BASS_STREAM_DECODE);
	int e = BASS_ErrorGetCode();

	CHAR *buf = (CHAR*)calloc(PACKETSIZE, sizeof(CHAR));
	dataBuf.buf = buf;
	dataBuf.len = PACKETSIZE;


	BASS_ChannelGetData(stream, dataBuf.buf, PACKETSIZE);
	e = BASS_ErrorGetCode();


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

	CHAR packet[MAXBUFLEN];
	//si -> bytesSent += bytesTransferred;

	if (error != 0 || bytesTransferred == 0)
	{
		//closeSendEverything( sinf, 0);
		return;
	}

	BASS_ChannelGetData(stream, dataBuf.buf, PACKETSIZE);
	int er = BASS_ErrorGetCode();

	if (WSASendTo((msi->workSock), &dataBuf, 1, &sentBytes, flags, (SOCKADDR*)msi->dstAddr, msi->dstAddrLen, &msi->overlapped, doSendMulticastWork) == SOCKET_ERROR)	{
		if (GetLastError() != WSA_IO_PENDING)
		{
			//closeRecvEverything(sinf, "Socket error");
			return;
		}
	}

	return;
}



DWORD WINAPI recvMulticast(LPVOID pVoid) {

	SocketInformation *si = (SocketInformation*)pVoid;
	World *world = si->world;
	
	si->streamHandle = initBass();

	DWORD recvBytes = 0;
	DWORD flags = 0;
	
	CHAR *buf = (CHAR*)calloc(PACKETSIZE, sizeof(CHAR));
	dataBuf.buf = buf;
	dataBuf.len = PACKETSIZE;

	if (!initMulticastComponent(&world->sockMulti, createClientBoundMulticastSocket))
		return FALSE;

	BASS_Init(-1, 44100, 0, 0, NULL);
	int er = BASS_ErrorGetCode();

	stream = BASS_StreamCreate(44100, 2, 0, STREAMPROC_PUSH, 0);
	er = BASS_ErrorGetCode();

	while (TRUE)
	{
		if (WSARecvFrom(world->sockMulti.workSock, &dataBuf, 1, &recvBytes, &flags, (SOCKADDR*)&world->sockMulti.lclAddr, &world->sockMulti.lclAddrLen, &si->overlapped, doRecvMulticastWork) == SOCKET_ERROR)
		{
			if (GetLastError() != WSA_IO_PENDING)
			{
				int err = GetLastError();//closeRecvEverything(&sinf, "Socket error");
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

	BASS_StreamPutData(stream, dataBuf.buf, PACKETSIZE);	
	int er = BASS_ErrorGetCode();

	BASS_ChannelPlay(stream, FALSE);
	er = BASS_ErrorGetCode();

	if (WSARecvFrom(world->sockMulti.workSock, &dataBuf, 1, &recvBytes, &flags, (SOCKADDR*)&world->sockMulti.lclAddr, &world->sockMulti.lclAddrLen, &si->overlapped, doRecvMulticastWork) == SOCKET_ERROR)
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