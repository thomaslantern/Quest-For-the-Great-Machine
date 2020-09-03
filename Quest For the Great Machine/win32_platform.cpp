#include <windows.h>
#include <iostream>

bool gameActive = true;

struct Render_State {
	int height, width;
	void* memory;

	BITMAPINFO bitmap_info;
};

struct Player {
	int posx, posy;

};

struct Map {
	int row_one[6], row_two[6], row_three[6];
	int row_four[6], row_five[6], row_six[6];
	void move_map_object();
};

Render_State render_state;

void move_map_object(Map map, Player player)
{
	int batman; // delete this nonsense immediately!!!!!!!!!!
}

#include "platform_inputs.cpp"
#include "gfxrender.cpp"



LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	LRESULT result = 0;
	switch (uMsg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
	{ gameActive = false; }
	break;
	case WM_SIZE: {
		RECT rect;
		GetClientRect(hwnd, &rect);
		render_state.width = rect.right - rect.left;
		render_state.height = rect.bottom - rect.top;

		int size = render_state.width * render_state.height * sizeof(unsigned int);

		if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
		render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
		render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
		render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
		render_state.bitmap_info.bmiHeader.biPlanes = 1;
		render_state.bitmap_info.bmiHeader.biBitCount = 32;
		render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;
		
	} break;
	default: {
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
	return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) 
{
	
	
	// Create Window Class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Window Class";
	window_class.lpfnWndProc = window_callback;

	// Register Window Class
	RegisterClass(&window_class);

	// Create Window
	HWND window = CreateWindow(window_class.lpszClassName, L"The Quest For The Great Machine",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
		680, 400, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	Input input = {};

	int level = 1;
	Player player;
	player.posx = 1;
	player.posy = 1;

	while (gameActive)
	{


		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			input.buttons[i].changed = false;
		}

		//INPUT
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			switch (message.message)
			{
			case WM_KEYUP:
			case WM_KEYDOWN:
			{
				unsigned int vk_code = (unsigned int)message.wParam;
				bool is_down = ((message.lParam & (1 << 31)) == 0);


				switch (vk_code)
				{
				case VK_UP:
				{
					input.buttons[BUTTON_UP].is_down = is_down;
					input.buttons[BUTTON_UP].changed = true;

				} break;
				case VK_DOWN:
				{
					input.buttons[BUTTON_DOWN].is_down = is_down;
					input.buttons[BUTTON_DOWN].changed = true;

				} break;
				case VK_LEFT:
				{
					input.buttons[BUTTON_LEFT].is_down = is_down;
					input.buttons[BUTTON_LEFT].changed = true;
					
				} break;
				case VK_RIGHT:
				{
					input.buttons[BUTTON_RIGHT].is_down = is_down;
					input.buttons[BUTTON_RIGHT].changed = true;
				
				} break;
				}
			} break;

			default:
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		//SIMULATE
		render_graphics(0XEEEEEE);
		//draw_rect(70, 0, 70, 300, 0X000000);
		if ((input.buttons[BUTTON_UP].is_down) && (input.buttons[BUTTON_UP].changed) && (player.posy < 6))
			player.posy += 1;

		else if ((input.buttons[BUTTON_DOWN].is_down) && (input.buttons[BUTTON_DOWN].changed) && (player.posy > 1))
			player.posy -= 1;

		else if ((input.buttons[BUTTON_LEFT].is_down) && (input.buttons[BUTTON_LEFT].changed) && (player.posx > 1))
			player.posx -= 1;
			
		else if ((input.buttons[BUTTON_RIGHT].is_down) && (input.buttons[BUTTON_RIGHT].changed) && (player.posx < 6))
			player.posx += 1;

		
		draw_map(player.posx, player.posy);

		
		
		

		//RENDER
		StretchDIBits(hdc, 0, 0, render_state.width, 
			render_state.height, 0, 0, render_state.width, 
			render_state.height, render_state.memory, 
			&render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}
}