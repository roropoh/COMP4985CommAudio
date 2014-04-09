#include "Master.h"

void CALLBACK doRetrieveSessionWork(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD inFlags);


INT initClient(UnicastComponent* sockSessn)
{
	// TCP
	if(createSendSocket(sockSessn) == 0) {
		// put error handling code here
		return 0;
	}
	return 1;
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

	MulticastSocketInformation msi;
	msi.overlapped = world->sockMulti.overlapped;
	msi.wsaEvent	 = &world->sockMulti.wsaEvent;
	msi.dstAddr    = &world->sockMulti.dstAddr;
	msi.dataBuf		 = world->buffs.dataBuf;
	msi.dstAddrLen = world->sockMulti.dstAddrLen;
	msi.buffer		 = world->buffs.buffer;
	msi.workSock	 = world->sockMulti.workSock;

	DWORD sentBytes	= 0;
	DWORD flags			= 0;

	if(connect(world->sockSessn.workSock, (SOCKADDR*)&world->sockSessn.inAddr, world->sockSessn.inAddrLen) == SOCKET_ERROR) {
		INT err = GetLastError();
		return FALSE;
	}

	while(TRUE) {
		if(WSARecv(msi.workSock, (LPWSABUF)msi.dataBuf, 1, &sentBytes, &flags, &msi.overlapped, doRetrieveSessionWork) == SOCKET_ERROR) {
			if(GetLastError() != WSA_IO_PENDING) {
				//closeRecvEverything(&sinf, "Socket error");
				int err = GetLastError();
				return FALSE;
			}
		}

		if(waitForWSAEventToComplete(msi.wsaEvent) == FALSE)
			return FALSE;

		//break;
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
	MulticastSocketInformation *msi = (MulticastSocketInformation*) overlapped;

	DWORD recvBytes = 0;
	DWORD flags			= 0;


	if( error != 0 || bytesTransferred == 0 ) {
		// close everything
		return;
	}

	CreateThread(0, 0, recvMulticast, (LPVOID)msi, 0, 0);
}

