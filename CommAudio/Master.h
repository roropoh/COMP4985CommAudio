#ifndef MASTER_H
#define MASTER_H

#include "Components.h"
#include "SmallStructs.h"

// Components.cpp
INT createBoundSocket(SocketsComponent* socks);
INT createSendSocket(SocketsComponent* socks);
INT initWorld(World* world);

// ServerMulticast.cpp
DWORD WINAPI sendMulticast(LPVOID pVoid);
INT createMulticastSocket(MulticastComponent* socks);

// ServerTcp.cpp
DWORD WINAPI waitForConnections(LPVOID pVoid);
INT initServer(SocketsComponent* sockTcp, MulticastComponent* sockUdp);

// Client.cpp
DWORD WINAPI retrieveSessionFromServer(LPVOID pVoid);
INT initClient(SocketsComponent* sockTcp, MulticastComponent* sockUdp);

#endif