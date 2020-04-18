
#include "vis.h"

t_vis_tools *vs;

SDL_Color			init_color(int r, int g, int b, int a)
{
	SDL_Color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 0;
	return (color);
}

int		prosess_press(int32_t x, int32_t y)
{
	int			i;
	int			j;

	i = 0;
	while (i < MEM_SIZE)
	{
		j = 0;
		while (j < 64)
		{
			if (10 + j * 24 < x && x < 24 + j * 24 && 15 +
				(i / 64) * 15 < y && y < 25 + (i / 64) * 15)
				return (i);
			j++;
			i++;
		}
	}
	return (-1);
}

void	track_events(int *indx, SDL_Event *e, bool *quit, int *stop)
{
	while (SDL_PollEvent(&(*e)) != 0)
	{
		if ((*e).type == SDL_QUIT)
		{
			*stop = 0;
			*quit = true;
		}
		else if ((*e).type == SDL_MOUSEBUTTONDOWN)
			*indx = prosess_press((*e).button.x, (*e).button.y);
		else if ((*e).type == SDL_KEYDOWN)
		{
			if ((*e).key.keysym.sym == SDLK_ESCAPE)
			{
				*stop = 0;
				*quit = true;
			}
			if ((*e).key.keysym.sym == SDLK_RIGHT)
				*stop = 0;
		}
	}
}

SDL_Rect		create_rect(int x, int y, int text_w, int text_h)
{
	SDL_Rect	dstrect;

	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = text_w;
	dstrect.h = text_h;
	return (dstrect);
}

void free_mem_font(void)
{
	SDL_FreeSurface(vs->txt_srfc);
	vs->txt_srfc = NULL;
	DESTROY_TXTR(vs->text);
}
