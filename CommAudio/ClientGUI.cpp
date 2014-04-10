#include "ClientGUI.h"

using namespace CommAudio;

int device;				// current input source
int input;				// current input source
char *recbuf;		// recording buffer
DWORD reclen;			// recording length

HRECORD rchan;		// recording channel
HSTREAM chan;			// playback channel

void ClientGUI::UpdateClientStatus(String ^ text)
{
	if (InvokeRequired)
	{
		Invoke(gcnew Action< String ^ >(this, &ClientGUI::UpdateClientStatus), text);
		return;
	}
	//client_status_box->Text = L"Bitch";
}

// buffer the recorded data
BOOL CALLBACK RecordingCallback(HRECORD handle, const void *buffer, DWORD length, void *user)
{
	// increase buffer size if needed
	if ((reclen%BUFSTEP) + length >= BUFSTEP) {
		recbuf = (char*)realloc(recbuf, ((reclen + length) / BUFSTEP + 1)*BUFSTEP);
		if (!recbuf) {
			rchan = 0;
			//Error("Out of memory!");
			//MESS(10,WM_SETTEXT,0,"Record");
			return FALSE; // stop recording
		}
	}
	// buffer the data
	memcpy(recbuf + reclen, buffer, length);
	reclen += length;
	return TRUE; // continue recording
}

void StartRecording()
{
	BASS_Init(-1, FREQ, 0, 0, NULL);
	InitDevice(1);

	WAVEFORMATEX *wf;
	if (recbuf) { // free old recording
		BASS_StreamFree(chan);
		chan = 0;
		free(recbuf);
		recbuf = NULL;
		// close output device before recording incase of half-duplex device
		BASS_Free();
	}

	// allocate initial buffer and make space for WAVE header
	recbuf = (char*)malloc(BUFSTEP);
	reclen = 44;
	// fill the WAVE header
	memcpy(recbuf, "RIFF\0\0\0\0WAVEfmt \20\0\0\0", 20);
	memcpy(recbuf + 36, "data\0\0\0\0", 8);
	wf = (WAVEFORMATEX*)(recbuf + 20);
	wf->wFormatTag = 1;
	wf->nChannels = CHANS;
	wf->wBitsPerSample = 16;
	wf->nSamplesPerSec = FREQ;
	wf->nBlockAlign = wf->nChannels*wf->wBitsPerSample / 8;
	wf->nAvgBytesPerSec = wf->nSamplesPerSec*wf->nBlockAlign;
	// start recording
	rchan = BASS_RecordStart(FREQ, CHANS, 0, RecordingCallback, 0);
	if (!rchan) {
		//Error("Couldn't start recording");
		free(recbuf);
		recbuf = 0;
		return;
	}
	//MESS(10,WM_SETTEXT,0,"Stop");
}

void StopRecording()
{
	BASS_ChannelStop(rchan);
	rchan = 0;
	// complete the WAVE header
	*(DWORD*)(recbuf + 4) = reclen - 8;
	*(DWORD*)(recbuf + 40) = reclen - 44;
	// enable "save" button
	// setup output device (using default device)
	if (!BASS_Init(-1, FREQ, 0, 0, NULL)) {
		// Error("Can't initialize output device");
		return;
	}
	// create a stream from the recording
	if (chan = BASS_StreamCreateFile(TRUE, recbuf, 0, reclen, 0)){}
	//EnableWindow(DLGITEM(11),TRUE); // enable "play" button
	else
		BASS_Free();

	BASS_ChannelPlay(chan, TRUE);
}

BOOL InitDevice(int device)
{
	BASS_RecordFree(); // free current device (and recording channel) if there is one
	// initalize new device
	if (!BASS_RecordInit(device)) {
		//Error("Can't initialize recording device");
		return FALSE;
	}
	{ // get list of inputs
		int c;
		const char *i;
		//MESS(13,CB_RESETCONTENT,0,0);
		for (c = 0; i = BASS_RecordGetInputName(c); c++) {
			//MESS(13,CB_ADDSTRING,0,i);
			if (!(BASS_RecordGetInput(c, NULL)&BASS_INPUT_OFF)) { // this one is currently "on"
				input = c;
				//MESS(13,CB_SETCURSEL,input,0);
				//UpdateInputInfo();
			}
		}
	}
	return TRUE;
}