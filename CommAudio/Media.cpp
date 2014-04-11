#include "Master.h"

INT initBass(HSTREAM *stream)
{
	BASS_Init(-1, 44100, 0, 0, NULL);
	(*stream) = BASS_StreamCreate(44100, 2, 0, STREAMPROC_PUSH, 0);

	return BASS_ErrorGetCode();
}

INT initBass(HSTREAM *stream, CHAR *fileName) 
{
	BASS_Init(-1, 44100, 0, 0, NULL);
	(*stream) = BASS_StreamCreateFile(FALSE, fileName, 0, 0, BASS_SAMPLE_LOOP | BASS_STREAM_DECODE);
	return BASS_ErrorGetCode();
}


INT ripSongPacket(HSTREAM *stream, CHAR *packet)
{
	BASS_ChannelGetData(*stream, packet, PACKETSIZE);
	return BASS_ErrorGetCode();
}

INT playSongPacket(HSTREAM *stream, CHAR* packet)
{
	INT error;
	error = BASS_StreamPutData(*stream, packet, PACKETSIZE);	
	error = BASS_ChannelPlay(*stream, FALSE);
	return BASS_ErrorGetCode();
}