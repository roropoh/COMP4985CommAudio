#include "MyForm.h"
#include "bass.h"
#include "ClientGUI.h"

using namespace std;
using namespace CommAudio;

[STAThreadAttribute]
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//HWND win = GetActiveWindow();

	Application::EnableVisualStyles();
	Application::Run(gcnew MyForm());
}
