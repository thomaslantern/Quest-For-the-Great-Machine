void render_graphics(unsigned int color)
{
	unsigned int* pixel = (unsigned int*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}

void draw_rect(int x0, int y0, int x1, int y1, unsigned int color)
{
	
	for (int y = y0; y < y1; y++) {
		unsigned int* pixel = (unsigned int*)render_state.memory + x0 + y*render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}

}

void draw_map(int x, int y)
{
	draw_rect(39, 29, 340, 330, 0X000000);



	for (int row = 1; row < 7; row++)
	{

		for (int col = 1; col < 7; col++)
		{
			unsigned int tile_color;
			int startx = 40 + ((col - 1) * 50);
			int starty = 30 + ((row - 1) * 50);

			switch (row)
			{


			case 1:
			{tile_color = 0XFFFFFF; }
			break;
			case 2:
			{tile_color = 0XDDDDDD; }
			break;
			case 3:
			{tile_color = 0XBBBBBB; }
			break;
			case 4:
			{tile_color = 0XFFFFFF; }
			break;
			case 5:
			{tile_color = 0XDDDDDD; }
			break;
			case 6:
			{tile_color = 0XBBBBBB; }
			break;
			}
			//draw_rect(startx, starty, startx + 50, starty + 50, tile_color); //starting: 40, 100, 90, 150
			draw_rect(startx, starty, startx + 49, starty + 49, tile_color); //starting: 40, 100, 90, 150

			// tiles are 49X49 (pretend 50X50??)
			// occupy middle of tile, half size of tile

			//main head
			// first tile is x: 40 to 90; y: 30 to 80
			int constx = (x * 50) - 50;
			int consty = (y * 50) - 50;

			draw_rect(57 + constx, 70 + consty, 62 + constx, 75 + consty, 0XAAAAAA);
			draw_rect(67 + constx, 70 + consty, 72 + constx, 75 + consty, 0XAAAAAA);
			draw_rect(52 + constx, 55 + consty, 77 + constx, 70 + consty, 0XAAAAAA);
			draw_rect(57 + constx, 60 + consty, 62 + constx, 65 + consty, 0X00BBAA);
			draw_rect(67 + constx, 60 + consty, 72 + constx, 65 + consty, 0X009988);
			draw_rect(57 + constx, 40 + consty, 72 + constx, 55 + consty, 0XAAAAAA);
			draw_rect(52 + constx, 45 + consty, 57 + constx, 55 + consty, 0X777777);
			draw_rect(72 + constx, 45 + consty, 77 + constx, 55 + consty, 0X777777);
			draw_rect(52 + constx, 40 + consty, 57 + constx, 45 + consty, 0X555555);
			draw_rect(72 + constx, 40 + consty, 77 + constx, 45 + consty, 0X555555);
			draw_rect(52 + constx, 30 + consty, 57 + constx, 35 + consty, 0X555555);
			draw_rect(72 + constx, 30 + consty, 77 + constx, 35 + consty, 0X555555);
			draw_rect(57 + constx, 30 + consty, 62 + constx, 40 + consty, 0X777777);
			draw_rect(67 + constx, 30 + consty, 72 + constx, 40 + consty, 0X777777);
			draw_rect(62 + constx, 45 + consty, 67 + constx, 50 + consty, 0X660066);

		}

	}
}