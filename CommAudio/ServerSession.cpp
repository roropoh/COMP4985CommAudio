#include "Master.h"

VOID CALLBACK doSendSessionWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags);
DWORD WINAPI sendSessionToClient(LPVOID pVoid);


INT initServer(SocketsComponent* sockSessn, MulticastComponent* sockMulti)
{
	sockSessn->wsaEvent = WSACreateEvent();
	sockMulti->wsaEvent = WSACreateEvent();

	ZeroMemory(&sockSessn->overlapped, sizeof(WSAOVERLAPPED));
	ZeroMemory(&sockMulti->overlapped, sizeof(WSAOVERLAPPED));

	// TCP
	if(createBoundSocket(sockSessn) == 0) {
		// put error handling code here
		return 0;
	}
	if(listen(sockSessn->listenSock, 5) == SOCKET_ERROR) {
		// put error handling code here
		return 0;
	}

	// UDP
	createServerBoundMulticastSocket(sockMulti);
	return 1;
}

DWORD WINAPI waitForConnections(LPVOID pVoid)
{
	World* world = (World*)pVoid;
	SocketsComponent* sockSessn = &world->sockSessn;

	SOCKADDR_IN* pinAddr		= &sockSessn->inAddr;
	INT*         pinAddrLen	= &sockSessn->inAddrLen;
	INT					 lsnSock		= sockSessn->listenSock;

	MSG thrdMsg;

	while(TRUE)
	{
		//PeekMessage(&thrdMsg, NULL, 0, 0, PM_NOREMOVE);
		//if(thrdMsg.message == WM_QUIT) {
		//	closesocket(sockSessn->workSock);
		//	break;
		//}

		if((sockSessn->workSock = accept(lsnSock, (SOCKADDR*)pinAddr, pinAddrLen)) != INVALID_SOCKET)
		{
			if(WSASetEvent(sockSessn->wsaEvent)  == FALSE) {
				// put error handling code here
				closesocket(sockSessn->workSock);
				return FALSE;
			}

			CreateThread(0, 0, sendSessionToClient, (LPVOID)world, 0, 0);
		}
	}

	return TRUE;
}



/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: sendTCPThread
--
-- DATE:		February 12th, 2014
--
-- REVISIONS:	None
--
-- DESIGNER:	Sam Youssef
--
-- PROGRAMMER:	Sam Youssef
--
-- INTERFACE:				DWORD WINAPI sendTCPThread(LPVOID pVoid)
--
--								LPVOID pVoid: standard void* passed to threads.
--								
-- RETURNS:		DWORD: exit status
--
-- NOTES:
-- This is the entry routine for the sendTCP thread. It acquires socket information and calls WSASend. WSASend is set to use 
-- a completion routine.
----------------------------------------------------------------------------------------------------------------------*/
DWORD WINAPI sendSessionToClient(LPVOID pVoid)
{
	World* world = (World*)pVoid;

	SocketInformation si;
	si.overlapped = &world->sockSessn.overlapped;
	si.dataBuf		= &world->buffs.dataBuf;
	si.wsaEvent		= &world->sockSessn.wsaEvent;
	si.buffer			= world->buffs.buffer;
	si.workSock		= world->sockSessn.workSock;

	DWORD sentBytes	= 0;
	DWORD flags			= 0;

	strcpy(si.buffer, "HOHO This is a packet 1024 bits long.");
	
	while(TRUE) {
		if(WSASend(si.workSock, (LPWSABUF)si.dataBuf, 1, &sentBytes, flags, si.overlapped, doSendSessionWork) == SOCKET_ERROR) {
			if(GetLastError() != WSA_IO_PENDING) {
				//closeSendEverything(&sinf, "Socket error");
				int err = GetLastError();
				return FALSE;
			}
		}

		if(waitForWSAEventToComplete(si.wsaEvent) == FALSE)
			return FALSE;
	}

	// close everything
	return TRUE;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: doTCPSendWork
--
-- DATE:		February 12th, 2014
--
-- REVISIONS:	None
--
-- DESIGNER:	Sam Youssef
--
-- PROGRAMMER:	Sam Youssef
--
-- INTERFACE:				void CALLBACK doTCPSendWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags)
--
--								DWORD error: error status of last send.
--								DWORD bytesTransferred: bytesTransferred during last send.
--								LPWSOVERLAPPED overlapped: the overlapped struct for during last send
--								DWORD inFlags: flags used for last send
--								
-- RETURNS:		void
--
-- NOTES:
-- This is the completion routine for WSASend. It reads from a file and calls WSASend again.
----------------------------------------------------------------------------------------------------------------------*/
VOID CALLBACK doSendSessionWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags)
{
	SocketInformation * si = (SocketInformation *) overlapped;

	DWORD sentBytes = 0;
	DWORD flags			= 0;


	if( error != 0 || bytesTransferred == 0 ) {
		// close everything
		return;
	}

	if(WSASend(si->workSock, (LPWSABUF)si->dataBuf, 1, &sentBytes, flags, si->overlapped, doSendSessionWork) == SOCKET_ERROR) {
		if(GetLastError() != WSA_IO_PENDING) {
			int err = GetLastError();
			//closeSendEverything(&sinf, "Socket error");
			return;
		}
	}
}

VOID packetizeAudioData(World *world){

}