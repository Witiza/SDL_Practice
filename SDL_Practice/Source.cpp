#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include "SDL\include\SDL.h"


#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")
#define MAX_SHOTS  100
#define WINDOW_HEIGHT 320
#define WINDOW_LENGHT 224

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);


	
	SDL_Window *window;
	SDL_Renderer *renderer;

	//SDL_CreateWindowAndRenderer(640, 320, SDL_WINDOW_RESIZABLE, &window, &renderer);
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 224, 320, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Surface* sprite = SDL_LoadBMP("images/valnus.bmp");
	SDL_Surface* background = SDL_LoadBMP("images/dank.bmp");
	SDL_Surface* shot = SDL_LoadBMP("images/laserlvl4.bmp");
	SDL_Texture* valnus = SDL_CreateTextureFromSurface(renderer, sprite);
	SDL_Texture* laser = SDL_CreateTextureFromSurface(renderer, shot);
	
	
	SDL_Texture* sea = SDL_CreateTextureFromSurface(renderer, background);

	SDL_Rect background1;
	background1.x = 0;
	background1.y = 0;
	background1.h = WINDOW_HEIGHT;
	background1.w = WINDOW_LENGHT;

	SDL_Rect background2;
	background2.x = 0;
	background2.y = WINDOW_HEIGHT;
	background2.h = WINDOW_HEIGHT;
	background2.w = WINDOW_LENGHT;


	SDL_Rect laserrect[MAX_SHOTS];
	for (int i = 0; i < MAX_SHOTS; i++)
	{
		laserrect[i].x = 2000;
		laserrect[i].y = 700;
		laserrect[i].h = 20;
		laserrect[i].w = 20;
	}

	int x = 200;
	int y = 200; 

	SDL_Rect spriteRect;
	spriteRect.x = x;
	spriteRect.y = y;
	spriteRect.h = 25;
	spriteRect.w = 25;


	
	bool flag = 0;
	bool space = false;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	int bulletcounter = 0;
	while (flag == 0)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			/* handle your event here */
			switch (event.type)
			{
				case SDL_KEYUP:
				{
					switch (event.key.keysym.scancode)
					{
						case SDL_SCANCODE_UP: up = false; break;
						case SDL_SCANCODE_DOWN: down = false; break;
						case SDL_SCANCODE_RIGHT: right = false; break;
						case SDL_SCANCODE_LEFT: left = false; break;
					}
					break;
				}
				case SDL_KEYDOWN:
				{
					switch (event.key.keysym.scancode)
					{	
					case SDL_SCANCODE_ESCAPE: flag = 1; break;
					case SDL_SCANCODE_UP: up = true; break;
					case SDL_SCANCODE_DOWN: down = true; break;
					case SDL_SCANCODE_RIGHT: right = true; break;
					case SDL_SCANCODE_LEFT: left = true; break;
					case SDL_SCANCODE_SPACE: space = true;   break;
					}
					break;
				}
			}
		}
			


			
			if (space == true)
			{
				laserrect[bulletcounter].x = x;
				laserrect[bulletcounter].y = y;
				bulletcounter++;
				if (bulletcounter > MAX_SHOTS)
				{
					bulletcounter = 0;
				}
				
				space = false;
			}

			if (up == true)
			{
				y -= 20;
			}
			 if (down == true)
			{
				y += 20;
			}
		 if (right == true)
			{
				x += 20;
			

			}
		if (left == true)
			{
				x -= 20;
		
			}
			
		

		for (int i = 0; i < MAX_SHOTS; i++)
		{
			laserrect[i].y -= 20;
		}
	
		background1.y -= 10;
		background2.y -= 10;

		if (background1.y <= -WINDOW_HEIGHT)
		{
			background1.y = WINDOW_HEIGHT;
		}

		if (background2.y <= -WINDOW_HEIGHT)
		{
			background2.y = WINDOW_HEIGHT;
		}

		
		spriteRect.x = x;
		spriteRect.y = y;
		

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, sea, NULL, &background1);
		SDL_RenderCopy(renderer, sea, NULL, &background2);
		for (int i = 0; i < MAX_SHOTS; i++)
		{
 			SDL_RenderCopy(renderer, laser, NULL, &laserrect[i]);
		}
		
		SDL_RenderCopy(renderer, valnus, NULL, &spriteRect);
		
		SDL_RenderPresent(renderer);
		/* do some other stuff here -- draw your app, etc. */
	}
	



	SDL_Quit();
	return 0;

}

