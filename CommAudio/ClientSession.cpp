#include "Master.h"

void CALLBACK doRetrieveSessionWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags);

INT initClient(SocketsComponent* sockSessn, MulticastComponent* sockMulti)
{
	sockSessn->wsaEvent = WSACreateEvent();
	sockMulti->wsaEvent = WSACreateEvent();

	ZeroMemory(&sockSessn->overlapped, sizeof(WSAOVERLAPPED));
	ZeroMemory(&sockMulti->overlapped, sizeof(WSAOVERLAPPED));

	// TCP
	if(createSendSocket(sockSessn) == 0) {
		// put error handling code here
		return 0;
	}
	return 1;
}


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
-- FUNCTION: recvTCPThread
--
-- DATE:		February 12th, 2014
--
-- REVISIONS:	None
--
-- DESIGNER:	Sam Youssef
--
-- PROGRAMMER:	Sam Youssef
--
-- INTERFACE:	DWORD WINAPI recvTCPThread (LPVOID pVoid)
--						LPVOID pVoid: standard void * pointer passed to threads.
--
-- RETURNS:		DWORD
--
-- NOTES:
-- Entry point for the receive TCP thread. It acquires socket information and calls WSARecv. Sets WSARecv to use a completion routine.
----------------------------------------------------------------------------------------------------------------------*/
DWORD WINAPI retrieveSessionFromServer(LPVOID pVoid)
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

	int err = connect(si.workSock, (SOCKADDR*)&world->sockSessn.inAddr, world->sockSessn.inAddrLen);

	err = GetLastError();
	
	while(TRUE) {
		if(WSARecv(si.workSock, (LPWSABUF)si.dataBuf, 1, &sentBytes, &flags, si.overlapped, doRetrieveSessionWork) == SOCKET_ERROR) {
			if(GetLastError() != WSA_IO_PENDING) {
				//closeRecvEverything(&sinf, "Socket error");
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
-- FUNCTION: doTCPRecvWork
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
-- This is the completion routine for WSARecv. It writes received data to a file and calls WSARecv again.
----------------------------------------------------------------------------------------------------------------------*/
void CALLBACK doRetrieveSessionWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags)
{
	SocketInformation * si = (SocketInformation *) overlapped;

	DWORD recvBytes = 0;
	DWORD flags			= 0;


	if( error != 0 || bytesTransferred == 0 ) {
		// close everything
		return;
	}

	if(WSARecv(si->workSock, (LPWSABUF)si->dataBuf, 1, &recvBytes, &flags, si->overlapped, doRetrieveSessionWork) == SOCKET_ERROR) {
		if(GetLastError() != WSA_IO_PENDING) {
			int err = GetLastError();
			//closeRecvEverything(&sinf, "Socket error");
			return;
		}
	}
}

