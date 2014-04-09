#ifndef MASTER_H
#define MASTER_H

#include "Components.h"
#include "SmallStructs.h"

// Shared.cpp
void initWSA();
BOOL waitForWSAEventToComplete(WSAEVENT* event);

// Components.cpp
INT createBoundSocket(UnicastComponent* sockSessn);
INT createSendSocket(UnicastComponent* sockSessn);
INT initWorld(World* world);

// Multicast.cpp
DWORD WINAPI recvMulticast(LPVOID pVoid); // client
DWORD WINAPI sendMulticast(LPVOID pVoid); // server
INT createServerBoundMulticastSocket(MulticastComponent* sockMulti);
INT createClientBoundMulticastSocket(MulticastComponent* sockMulti);


// ServerSession.cpp
DWORD WINAPI waitForConnections(LPVOID pVoid);
INT initServer(UnicastComponent* sockSessn);

// ClientSession.cpp
DWORD WINAPI retrieveSessionFromServer(LPVOID pVoid);
INT initClient(UnicastComponent* sockSessn);

#endif