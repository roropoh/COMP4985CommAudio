#include "WriteToFile.h"

#ifdef _BIG_ENDIAN
inline DWORD le_32(DWORD v)
{
	return (v>>24)|((v>>8)&0xff00)|((v&0xff00)<<8)|(v<<24);
}
inline WORD le_16(WORD v)
{
	return (v>>8)|(v<<8);
}
#else
#define le_32(v) (v)
#define le_16(v) (v)
#endif

FILE *fp;
BASS_CHANNELINFO channelInfo;
DWORD p;
WAVEFORMATEX wf;

void CreateFileHeader(HSTREAM stream)
{
	if ((fp = fopen("stream.wav", "wb")) == 0) 
	{
		//MessageBox::Show("Error creating file to save the stream.");
		//return EXIT_FAILURE;
	}

	//get and save the channel information
	BASS_ChannelGetInfo(stream, &channelInfo);

	wf.wFormatTag=1;
	wf.nChannels=channelInfo.chans;
	wf.wBitsPerSample=(channelInfo.flags&BASS_SAMPLE_8BITS?8:16);
	wf.nBlockAlign=wf.nChannels*wf.wBitsPerSample/8;
	wf.nSamplesPerSec=channelInfo.freq;
	wf.nAvgBytesPerSec=wf.nSamplesPerSec*wf.nBlockAlign;

	//write the header to the file first.
	fwrite("RIFF\0\0\0\0WAVEfmt \20\0\0\0",20,1,fp);
	fwrite(&wf,16,1,fp);
	fwrite("data\0\0\0\0",8,1,fp);
}

void SaveFile(WSABUF buffer)
{
	fwrite(buffer.buf, sizeof(char), buffer.len, fp);
}

void StopSaveFile()
{
	fflush(fp);
	p=ftell(fp);
	fseek(fp,4,SEEK_SET);
	putw(le_32(p-8),fp);
	fflush(fp);
	fseek(fp,40,SEEK_SET);
	putw(le_32(p-44),fp);
	fflush(fp);
	fclose(fp);

	BASS_Free();
}
