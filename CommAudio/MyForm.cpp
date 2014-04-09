#include "MyForm.h"

using namespace CommAudio;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Application::EnableVisualStyles();
	Application::Run(gcnew MyForm());
}