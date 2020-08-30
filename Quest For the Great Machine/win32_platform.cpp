#include <windows.h>

static int window_callback()
{
	return;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) 
{
	bool gameOver = false;
	

	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Game Window Class";
	window_class.lpfnWndProc = window_callback;


	while (!gameOver) 
	{
		INPUT input = "frig off";
	}
}