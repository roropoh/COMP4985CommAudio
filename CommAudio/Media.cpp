#include "Master.h"


HSTREAM initBass(CHAR* fileName)
{
	HSTREAM streamHandle; // Handle for open stream

	// Initialize BASS with default sound device and 44100Hz Sample rate
	BASS_Init(-1, 44100, 0, 0, NULL);

	// Load your soundfile and play it
	streamHandle = BASS_StreamCreateFile(FALSE, fileName, 0, 0, 0);

	return streamHandle;
}


VOID ripSongPacket(FLOAT* packet, HSTREAM streamHandle)
{
	//BASS_ChannelPlay(streamHandle, FALSE);
	
	BASS_ChannelGetData(streamHandle, packet, PACKETSIZE);
	BASS_StreamPutData(streamHandle, packet, PACKETSIZE);
}