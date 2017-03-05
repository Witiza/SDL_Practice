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

	//SDL_CreateWindowAndRenderer(640, 320, SDL_WINDOW_RESIZABLE, &window, &renderer);
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 398, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface* sprite = SDL_LoadBMP("images/surf.bmp");
	SDL_Surface* background = SDL_LoadBMP("images/dank.bmp");
	SDL_Texture* penis = SDL_CreateTextureFromSurface(renderer, sprite);
	SDL_Texture* sea = SDL_CreateTextureFromSurface(renderer, background);


	



	
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
					x -= 20;
					break;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					x += 20;
					break;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					y += 20;
					break;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_UP)
				{
					y -= 20;
					break;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_I)
				{
					y -= 20;
					break;
				}
			}
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderClear(renderer);

			SDL_Rect spriteRect;
			spriteRect.x = x;
			spriteRect.y = y;
			spriteRect.h = 100;
			spriteRect.w = 100;

			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, sea, NULL, NULL);
			SDL_RenderCopy(renderer, penis, NULL, &spriteRect);
			SDL_RenderPresent(renderer);
		}
		
		/* do some other stuff here -- draw your app, etc. */
	}
	



	SDL_Quit();
	return 0;

}

