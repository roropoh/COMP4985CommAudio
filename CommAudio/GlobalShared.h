#ifndef SHAREDHDRS_H
#define SHAREDHDRS_H

#define MAXBUFLEN 1024
#define PACKETSIZE 1024
#define FREQ 44100
#define BUFSTEP 200000
#define CHANS 2

#define DEFAULT_SERVERPORT 7000

#define SERVER 1
#define CLIENT 2

#define TERMINATE_THRD WM_USER+1

#include <winsock2.h> // components.h
#include <ws2tcpip.h> // components.h
#include <Windows.h>  // all of 'em


#endif