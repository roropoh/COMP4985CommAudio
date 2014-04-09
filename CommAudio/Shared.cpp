#include "Master.h"



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
BOOL waitForWSAEventToComplete(WSAEVENT* event)
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