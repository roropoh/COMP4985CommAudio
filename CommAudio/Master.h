#ifndef MASTER_H
#define MASTER_H

#include "Components.h"
#include "SmallStructs.h"
#include "WriteToFile.h"

// Shared.cpp
void initWSA();
BOOL waitForWSAEventToComplete(WSAEVENT* event);

// Components.cpp
INT createBoundSocket(UnicastComponent* sockSessn);
INT createSendSocket(UnicastComponent* sockSessn);
INT initWorld(World* world);
INT initMulticastComponent(MulticastComponent* sockMulti, INT createSocketType(MulticastComponent*));


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

//Media.cpp
INT initBass (HSTREAM* stream);
INT initBass (HSTREAM* stream, CHAR* fileName);
INT ripSongPacket (HSTREAM* stream, CHAR* packet);
INT playSongPacket(HSTREAM* stream, CHAR* packet);

// ClientGUI.cpp
BOOL CALLBACK RecordingCallback(HRECORD handle, const void *buffer, DWORD length, void *user);
void StartRecording();
void StopRecording();
BOOL InitDevice(int device);

#endif