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

void draw_map(int x, int y, Map map)
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

			
				
			switch (map.rows_cols[col - 1][row - 1])
			{
			case 0:	
			{
			}break;
			case 1:
			{
				draw_rect(startx, starty, startx + 49, starty + 49, 0X999999);
				draw_rect(startx + 15, starty, startx + 35, starty + 40, 0XAAAAAA);
				draw_rect(startx + 5, starty + 5, startx + 15, starty + 15, 0X0000BB);
				draw_rect(startx + 5, starty + 10, startx + 15, starty + 15, 0X006666);
				draw_rect(startx + 5, starty + 20, startx + 15, starty + 25, 0XFFFF00);
				draw_rect(startx + 5, starty + 35, startx + 15, starty + 40, 0X0000BB);
				draw_rect(startx + 35, starty + 5, startx + 45, starty + 10, 0X00BB00);
				draw_rect(startx + 35, starty + 15, startx + 45, starty + 20, 0X0000AA);
				draw_rect(startx + 35, starty + 25, startx + 45, starty + 30, 0X00FF00);
				draw_rect(startx + 35, starty + 35, startx + 45, starty + 40, 0X0000BB);

			}break;
			case 2:
			{
				draw_rect(startx + 10, starty + 25, startx + 20, starty + 30, 0XFF0000);
				draw_rect(startx + 10 , starty + 40, startx + 25, starty + 45, 0XFF0000);
				draw_rect(startx + 20, starty + 10, startx + 25, starty + 40, 0XFF0000);
				draw_rect(startx + 25, starty + 10, startx + 40, starty + 15, 0XFF0000);
				//996633 BOX
				draw_rect(startx + 25, starty + 15, startx + 40, starty + 30, 0X996633);
				draw_rect(startx + 25, starty + 30, startx + 40, starty + 45, 0X885522);
				//000000 WHEEL
				draw_rect(startx + 15, starty, startx + 20, starty + 5, 0X000000);
				draw_rect(startx + 10, starty + 5, startx + 15, starty + 10, 0X000000);
				draw_rect(startx + 20, starty + 5, startx + 25, starty + 10, 0X000000);
				draw_rect(startx + 15, starty + 10, startx + 20, starty + 15, 0X000000);
				draw_rect(startx + 15, starty + 5, startx + 20, starty + 10, 0X666666);

			}break;
			case 3:
			{
				draw_rect(startx, starty, startx + 49, starty + 49, 0X008899);
			}break;
			}

		/*	Map levelmap = {
		0, 0, 0, 0, 0, 1,
		0, 2, 1, 0, 0, 1,
		0, 0, 0, 0, 0, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 3 };
		
		[0][0]. [1][0], [2][0], etc
		*/


			

		}

	}

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