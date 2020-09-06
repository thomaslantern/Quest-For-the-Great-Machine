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
	int lives = 3;
};

struct Map {
	int rows_cols[6][6];
	
};

Player player;

Render_State render_state;


// Map states:
// 0 - blank space or player-occupied space
// 1 - Obstacle that cannot be moved (Server rack)
// 2 - Dolly that can be moved if there is nothing in the way
// 3 - Exit to level
// 4 - Laser that aims south
// 5 - Laser that aims north
// 6 - Laser that aims west
// 7 - Laser that aims east
// 8 - Mirror that blocks laser
// 9 - Dead Robot

Map map_one = {
		0, 0, 1, 0, 0, 0,
		0, 1, 0, 0, 1, 0,
		2, 2, 0, 0, 1, 2,
		0, 1, 0, 2, 0, 0,
		1, 0, 2, 2, 2, 0,
		1, 0, 0, 0, 0, 3 };

Map map_two = {
		0, 1, 0, 0, 2, 0,
		2, 2, 0, 0, 2, 0,
		0, 0, 1, 0, 0, 0,
		0, 0, 1, 0, 2, 1,
		0, 0, 2, 1, 0, 0,
		0, 2, 0, 0, 0, 3 };

Map map_three = {
		0, 0, 0, 0, 0, 1,
		2, 0, 1, 1, 2, 0,
		0, 2, 0, 0, 0, 2,
		0, 1, 0, 0, 1, 0,
		2, 0, 2, 0, 2, 0,
		0, 0, 0, 2, 0, 3 };

Map map_four = {
		0, 2, 0, 2, 0, 2,
		2, 0, 2, 2, 2, 0,
		0, 2, 0, 2, 0, 2,
		2, 0, 2, 0, 2, 0,
		0, 2, 0, 2, 2, 0,
		0, 0, 2, 0, 0, 3 };

Map map_five = {
		0, 0, 0, 0, 0, 0,
		0, 0, 8, 0, 0, 0,
		0, 0, 0, 1, 8, 0,
		0, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 4,
		0, 0, 6, 0, 0, 3 };

Map game_over = {
		0, 1, 9, 9, 9, 9,
		1, 9, 9, 9, 9, 9,
		9, 9, 9, 9, 9, 9,
		9, 9, 9, 9, 9, 9,
		9, 9, 9, 9, 9, 9,
		9, 9, 9, 9, 9, 9 };



Map map_list[5] = { map_one, map_two, map_three, map_four, map_five };

Map current_level = map_list[0];
int level = 1;
bool move_map_object(Map map, int desired_x, int desired_y, char direction)
{
	if (map.rows_cols[desired_x - 1][desired_y - 1] == 0) return true;
	else if (map.rows_cols[desired_x - 1][desired_y - 1] == 9)
	{
		current_level.rows_cols[desired_x - 1][desired_y - 1] = 0;
		return true;
	}
	else if (
		(map.rows_cols[desired_x - 1][desired_y - 1] == 1) || 
		(map.rows_cols[desired_x - 1][desired_y - 1] == 4) ||
		(map.rows_cols[desired_x - 1][desired_y - 1] == 5) ||
		(map.rows_cols[desired_x - 1][desired_y - 1] == 6) ||
		(map.rows_cols[desired_x - 1][desired_y - 1] == 7)) return false;
	else if ((map.rows_cols[desired_x - 1][desired_y - 1] == 2) || (map.rows_cols[desired_x - 1][desired_y - 1] == 8))
	{
		switch (direction)
		{
		case 'N':
		{
			if (((desired_y + 1) <= 6) && (move_map_object(map, desired_x, (desired_y + 1), 'D')))
			{
				current_level.rows_cols[desired_x - 1][desired_y] = current_level.rows_cols[desired_x - 1][desired_y - 1];
				current_level.rows_cols[desired_x - 1][desired_y - 1] = 0;
				return true;
			}
			else return false;
		} break;
		case 'S':
		{
			if (((desired_y - 1) >= 1) && (move_map_object(map, desired_x, (desired_y - 1), 'D')))
			{
				current_level.rows_cols[desired_x - 1][desired_y - 2] = current_level.rows_cols[desired_x - 1][desired_y - 1];
				current_level.rows_cols[desired_x - 1][desired_y - 1] = 0;
				return true;
			}
			else return false;
		} break;
		case 'E':
		{
			if (((desired_x + 1) <= 6) && (move_map_object(map, (desired_x + 1), desired_y, 'D')))
			{
				current_level.rows_cols[desired_x][desired_y - 1] = current_level.rows_cols[desired_x - 1][desired_y - 1];
				current_level.rows_cols[desired_x - 1][desired_y - 1] = 0;
				return true;
			}
			else return false;
		} break;
		case 'W':
		{
			if (((desired_x - 1) >= 1) && (move_map_object(map, (desired_x - 1), desired_y, 'D')))
			{
				current_level.rows_cols[desired_x - 2][desired_y - 1] = current_level.rows_cols[desired_x - 1][desired_y - 1];
				current_level.rows_cols[desired_x - 1][desired_y - 1] = 0;
				return true;
			}
			else return false;
		} break;
		case 'D':
		{
			return false;
		}
		default: return false;
		}
	}
	else if (map.rows_cols[desired_x - 1][desired_y - 1] == 3)
	{
		if (direction != 'D')
		{
			player.posx = 1;
			player.posy = 1;
			if (level < 5)
			{
				level += 1;
				current_level = map_list[level - 1]; 
			}
			else
			{
				current_level = game_over;
			}


		}
		return false;
	}
	
	
	
}
	

void kill_robot(int posx, int posy)
{
	Map current_map = map_list[level - 1];
	if (current_map.rows_cols[posx - 1][posy - 1] == 0)
	{
		current_level.rows_cols[posx - 1][posy - 1] = 9;
	}
	
	player.lives -= 1;
	if (player.lives == 0)
		current_level = game_over;
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
	HWND window = CreateWindow(window_class.lpszClassName, L"The Quest For The Great Machine - DEMO",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
		680, 400, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	Input input = {};

	

	
	

	
	
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
				case 0X51:
				{
					current_level = map_list[0];
					player.posx = 1;
					player.posy = 1;
					player.lives = 3;
					level = 1;
				}break;
				case 0X52:
				{
					
					
					int deadrobotx = player.posx;
					int deadroboty = player.posy;

					if ((player.posx != 1) || (player.posy != 1))
					{
						
						current_level = map_list[level - 1];
						kill_robot(deadrobotx, deadroboty);
						
						player.posx = 1;
						player.posy = 1;
					}


					
				}break;
				}
			} break;

			default:
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		//SIMULATE
		render_graphics(0XEEEEEE);
		
		if ((input.buttons[BUTTON_UP].is_down) && (input.buttons[BUTTON_UP].changed) && (player.posy < 6))
		{
			if (move_map_object(current_level, player.posx, (player.posy + 1), 'N')) player.posy += 1;
			
		}
			

		else if ((input.buttons[BUTTON_DOWN].is_down) && (input.buttons[BUTTON_DOWN].changed) && (player.posy > 1))
		{
			if (move_map_object(current_level, player.posx, (player.posy - 1), 'S')) player.posy -= 1;
		}
		else if ((input.buttons[BUTTON_LEFT].is_down) && (input.buttons[BUTTON_LEFT].changed) && (player.posx > 1))
		{
			if (move_map_object(current_level, (player.posx - 1), player.posy, 'W')) player.posx -= 1;
		}
		else if ((input.buttons[BUTTON_RIGHT].is_down) && (input.buttons[BUTTON_RIGHT].changed) && (player.posx < 6))
		{
			if (move_map_object(current_level, (player.posx + 1), player.posy, 'E')) player.posx += 1;
		}

		
		draw_map(player.posx, player.posy, current_level);

		
		
		

		//RENDER
		StretchDIBits(hdc, 0, 0, render_state.width, 
			render_state.height, 0, 0, render_state.width, 
			render_state.height, render_state.memory, 
			&render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}
}