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
	unsigned int* pixel = (unsigned int*)render_state.memory;
	for (int y = y0; y < y1; y++) {
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}

}