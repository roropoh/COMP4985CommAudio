#include "MyForm.h"

using namespace CommAudio;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WORD wVersionRequested;
	WSADATA WSAData;

	wVersionRequested = MAKEWORD(2, 2);

	//Call WSAStartup
	if (WSAStartup(wVersionRequested, &WSAData) != 0){
		MessageBox::Show("WSAStartup failed with error (" + WSAGetLastError() + ")", "Error");
		WSACleanup();
		exit(1);
	}

	Application::EnableVisualStyles();
	Application::Run(gcnew MyForm());
}