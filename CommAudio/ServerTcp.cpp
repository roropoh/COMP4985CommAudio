#include "Master.h"

VOID CALLBACK doSendSessionWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags);
DWORD WINAPI sendSessionToClient(LPVOID pVoid);


INT initServer(SocketsComponent* sockTcp, MulticastComponent* sockUdp)
{
	sockTcp->wsaEvent = WSACreateEvent();
	sockUdp->wsaEvent = WSACreateEvent();

	ZeroMemory(&sockTcp->overlapped, sizeof(WSAOVERLAPPED));
	ZeroMemory(&sockUdp->overlapped, sizeof(WSAOVERLAPPED));

	// TCP
	if(createBoundSocket(sockTcp) == 0) {
		// put error handling code here
		return 0;
	}
	if(listen(sockTcp->listenSock, 5) == SOCKET_ERROR) {
		// put error handling code here
		return 0;
	}

	// UDP
	createMulticastSocket(sockUdp);
	return 1;
}

DWORD WINAPI waitForConnections(LPVOID pVoid)
{
	World* world = (World*)pVoid;
	SocketsComponent* sockTcp = &world->sockTcp;

	SOCKADDR_IN* pinAddr		= &sockTcp->inAddr;
	INT*         pinAddrLen	= &sockTcp->inAddrLen;
	INT					 lsnSock		= sockTcp->listenSock;

	while( TRUE )
	{
		sockTcp->workSock = accept(lsnSock, (SOCKADDR*)pinAddr, pinAddrLen);

		if( WSASetEvent(sockTcp->wsaEvent)  == FALSE) {
			// put error handling code here
			int err = GetLastError();
			return FALSE;
		}

		CreateThread(0, 0, sendSessionToClient, (LPVOID)world, 0, 0);
	}

	return TRUE;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: waitWSAEvntCompletes
--
-- DATE:		February 12th, 2014
--
-- REVISIONS:	None
--
-- DESIGNER:	Sam Youssef
--
-- PROGRAMMER:	Sam Youssef
--
-- INTERFACE:	BOOL waitWSAEvntCompletes( SOCKET_INFORMATION * sinf )
--
--						SOCKET_INFORMATION * sinf: pointer to a struct which contains a Handle to the asynchronous event
--
-- RETURNS:		BOOL: true if asynchronous operation succeeds, false otherwise
--
-- NOTES:
-- This function basically enters into an infinite loop to wait for an asynchronous send or receive operation to complete.
-- It exits with a return value of true the operation is complete. On failure, it exits with a return value of false.
----------------------------------------------------------------------------------------------------------------------*/
static BOOL waitForWSAEventToComplete(WSAEVENT* event)
{
	WSAEVENT eventsArray[1] = { *event };
	DWORD index;

	while( TRUE ) {
		index = WSAWaitForMultipleEvents( 1, eventsArray, FALSE, WSA_INFINITE, TRUE);
		switch(index) {
			case WSA_WAIT_FAILED: return FALSE;
			case WAIT_IO_COMPLETION: break;
		}
	}
	WSAResetEvent(*event);
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
	si.overlapped = &world->sockTcp.overlapped;
	si.dataBuf		= &world->buffs.dataBuf;
	si.wsaEvent		= &world->sockTcp.wsaEvent;
	si.buffer			= world->buffs.buffer;
	si.workSock		= world->sockTcp.workSock;

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