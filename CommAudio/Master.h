#ifndef MASTER_H
#define MASTER_H

#include "Components.h"
#include "SmallStructs.h"

// Shared.cpp
void initWSA();
BOOL waitForWSAEventToComplete(WSAEVENT* event);

// Components.cpp
INT createBoundSocket(SocketsComponent* sockSessn);
INT createSendSocket(SocketsComponent* sockSessn);
INT initWorld(World* world);

// Multicast.cpp
DWORD WINAPI sendMulticast(LPVOID pVoid);
INT createServerBoundMulticastSocket(MulticastComponent* sockMulti);

// ServerSession.cpp
DWORD WINAPI waitForConnections(LPVOID pVoid);
INT initServer(SocketsComponent* sockSessn, MulticastComponent* sockMulti);

// ClientSession.cpp
DWORD WINAPI retrieveSessionFromServer(LPVOID pVoid);
INT initClient(SocketsComponent* sockSessn, MulticastComponent* sockMulti);

#endif