#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include "SDL\include\SDL.h"

#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Surface *surface;
	Uint32 mask, gmask, bmask, amask;
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_CreateWindowAndRenderer(640, 320, SDL_WINDOW_RESIZABLE, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	SDL_RenderClear(renderer);

	SDL_Rect r;
	r.x = 66;
	r.y = 66;
	r.w = 66;
	r.h = 66;

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	SDL_RenderFillRect(renderer, &r);

	SDL_RenderPresent(renderer);
	int x = 0;
	int y = 0;
	bool flag = 0;
	while (flag == 0)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			/* handle your event here */
			switch (event.type)
				case SDL_KEYDOWN:
			{
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					flag = 1;
					break;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					x -= 10;
					break;
				}
			}
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

			SDL_RenderClear(renderer);

			SDL_RenderPresent(renderer);



			r.x = x;
			r.y = y;
			r.w = 66;
			r.h = 66;

			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

			SDL_RenderFillRect(renderer, &r);

			SDL_RenderPresent(renderer);
		}
		
		/* do some other stuff here -- draw your app, etc. */
	}
	



	SDL_Quit();
	return 0;

}

