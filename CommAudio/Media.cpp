#include "Master.h"

HSTREAM initBass()
{
	HSTREAM streamHandle;

	// Initialize BASS with default sound device and 44100Hz Sample rate
	BASS_Init(-1, 44100, 0, 0, NULL);

	streamHandle = BASS_StreamCreate(44100, 2, 0, STREAMPROC_PUSH, 0);

	return streamHandle;
}

HSTREAM initBass(CHAR* fileName)
{
	HSTREAM streamHandle; // Handle for open stream

	// Initialize BASS with default sound device and 44100Hz Sample rate
	BASS_Init(-1, 44100, 0, 0, NULL);

	// Load your soundfile and play it
	streamHandle = BASS_StreamCreateFile(FALSE, "C:\\Users\\pc1\\Documents\\GitHub\\COMP4985CommAudio\\CommAudio\\ladyGaga.mp3", 0, 0, BASS_SAMPLE_LOOP | BASS_STREAM_DECODE);

	return streamHandle;
}


BOOL ripSongPacket(CHAR* packet, HSTREAM streamHandle)
{

	BASS_ChannelGetData(streamHandle, packet, PACKETSIZE);
	//BASS_StreamPutData(streamHandle, packet, PACKETSIZE);

	return TRUE;
}

BOOL playSongPacket(CHAR* packet, HSTREAM streamHandle)
{
	BASS_StreamPutData(streamHandle, packet, PACKETSIZE);	
	BASS_ChannelPlay(streamHandle, FALSE);

	return TRUE;
}

DWORD WINAPI play(LPVOID pVoid) {

	HSTREAM *stream = (HSTREAM*)pVoid;

	BASS_ChannelPlay(*stream, FALSE);
	int er = BASS_ErrorGetCode();
	return false;
}