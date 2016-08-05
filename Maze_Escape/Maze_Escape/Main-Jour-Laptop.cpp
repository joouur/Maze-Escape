#include <stdio.h>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gHell = NULL;

// Prototype Functions
// Initialize, Start SDL and create Window.
bool init();
//Load media
bool loadMedia();
// Shut down SDL
void close();


int main(int argc, char * args[])
{
	if (!init())
	{
		printf("Fail to initialize!\n");
	}
	else
	{
		if (!loadMedia())
			printf("Failed to load media!\n");
		else
		{
			SDL_BlitSurface(gHell, NULL, gScreenSurface, NULL);
			SDL_UpdateWindowSurface(gWindow);
			SDL_Delay(2000);
		}
		close();
	}
	return 0;
}

bool init()
{
	bool open = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s/n", SDL_GetError());
		open = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Maze Escape", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s/n", SDL_GetError());
			open = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return open;
}

bool loadMedia()
{
	bool open = true;

	gHell = SDL_LoadBMP("Images\\panda.bmp");
	if (gHell == NULL)
	{
		printf("Unable to load image %s! SDL_Error: %s\n", "panda.bmp", SDL_GetError());
		open = false;
	}
	return open;
}

void close()
{
	SDL_FreeSurface(gHell);
	gHell = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}