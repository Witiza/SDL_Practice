#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_image.h"


#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")
#pragma comment( lib, "SDL/libx86/SDL2_image.lib")
#define MAX_SHOTS  100
#define WINDOW_HEIGHT 640
#define WINDOW_LENGHT 448
#define CHARACTER_SPEED 5
#define BULLET_SPEED 10
#define BACKGROUND_SPEED 10
#define FRAME_SPEED 4

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	IMG_INIT_PNG;

	SDL_Window *window;
	SDL_Renderer *renderer;

	//SDL_CreateWindowAndRenderer(640, 320, SDL_WINDOW_RESIZABLE, &window, &renderer);
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_LENGHT, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Surface* sprite = IMG_Load("images/reimu sprite.png");
	SDL_Surface* background = IMG_Load("images/Mine.jpg");
	
	SDL_Texture* valnus = SDL_CreateTextureFromSurface(renderer, sprite);
	SDL_Texture* laser = SDL_CreateTextureFromSurface(renderer, sprite);
	
	
	SDL_Texture* sea = SDL_CreateTextureFromSurface(renderer, background);

	SDL_Rect backgroundsource;
	backgroundsource.x = 0;
	backgroundsource.y = 0;
	backgroundsource.h = WINDOW_HEIGHT;
	backgroundsource.w = WINDOW_LENGHT;

	SDL_Rect background1;
	background1.x = 0;
	background1.y = 0;
	background1.h = WINDOW_HEIGHT;
	background1.w = WINDOW_LENGHT;

	SDL_Rect background2;
	background2.x = 0;
	background2.y = -WINDOW_HEIGHT;
	background2.h = WINDOW_HEIGHT;
	background2.w = WINDOW_LENGHT;

	SDL_Rect lasersourteSprite;
	lasersourteSprite.x = 0;
	lasersourteSprite.y = 161;
	lasersourteSprite.h = 20;
	lasersourteSprite.w = 20;


	SDL_Rect laserrect[MAX_SHOTS];
	for (int i = 0; i < MAX_SHOTS; i++)
	{
		laserrect[i].x = 2000;
		laserrect[i].y = 700;
		laserrect[i].h = 60;
		laserrect[i].w = 60;
	}

	int x = 200;
	int y = 200; 


	

	SDL_Rect spriteRect;
	spriteRect.x = x;
	spriteRect.y = y;
	spriteRect.h = 75;
	spriteRect.w =75;

	int framecounter = 0;
	int xsprite = 0;
	int ysprite = 0;
	bool flag = 0;
	bool space = false;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool lateralmovement = false;
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
					case SDL_SCANCODE_C: space = true;   break;
					}
					break;
				}
			}
		}
			
		SDL_Rect sourceSprite;

		sourceSprite.x = xsprite;
		sourceSprite.y = ysprite;
		sourceSprite.h = 51;
		sourceSprite.w = 32;
		
		switch (framecounter)
		{
		case 0: xsprite = 0; break;
		case FRAME_SPEED: xsprite = 32; break;
		case FRAME_SPEED*2: xsprite = 64; break;
		case FRAME_SPEED*3: xsprite = 96; break;
		case FRAME_SPEED*4: xsprite = 128; break;
		case FRAME_SPEED*5: xsprite = 160; break;
		case FRAME_SPEED * 6: xsprite = 192; break;
		case FRAME_SPEED * 7: xsprite = 224; framecounter = 0; break;
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
				y -= CHARACTER_SPEED;
			}
			 if (down == true)
			{
				y += CHARACTER_SPEED;
			}
		 if (right == true)
			{
				x += CHARACTER_SPEED;
			}
		if (left == true)
			{
				x -= CHARACTER_SPEED;
		
			}
			
		

		for (int i = 0; i < MAX_SHOTS; i++)
		{
			laserrect[i].y -= BULLET_SPEED;
		}
	
		background1.y += BACKGROUND_SPEED;
		background2.y += BACKGROUND_SPEED;

		if (background1.y >= WINDOW_HEIGHT)
		{
			background1.y = -WINDOW_HEIGHT;
		}

		if (background2.y >= WINDOW_HEIGHT)
		{
			background2.y = -WINDOW_HEIGHT;
		}

		
		spriteRect.x = x;
		spriteRect.y = y;
		

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, sea, &backgroundsource, &background1);
		SDL_RenderCopy(renderer, sea, &backgroundsource, &background2);
		for (int i = 0; i < MAX_SHOTS; i++)
		{
 			SDL_RenderCopy(renderer, laser, &lasersourteSprite, &laserrect[i]);
		}
		
		SDL_RenderCopy(renderer, valnus, &sourceSprite, &spriteRect);
		
		SDL_RenderPresent(renderer);
		framecounter++;
		/* do some other stuff here -- draw your app, etc. */
	}
	



	SDL_Quit();
	return EXIT_SUCCESS;

}

