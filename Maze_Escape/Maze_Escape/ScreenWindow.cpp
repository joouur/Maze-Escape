#include "ScreenWindow.h"


#pragma region StartFunctions
ScreenWindow::ScreenWindow()
{
	if (!init())
	{
		printf("Failed to initialize! SDL_Error: %s", SDL_GetError());
	}
	else
	{

	}
}


ScreenWindow::~ScreenWindow()
{
}

bool ScreenWindow::init()
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
			//gScreenSurface = SDL_GetWindowSurface(gWindow);
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Failed to create Render! SDL_Error: %s.\n", SDL_GetError());
				open = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("Failed to initilize SDL_Image! SDL_Image_Error: %s", SDL_GetError());
					open = false;
				} // Image_Init if
			} // RenderDrawColor else
		} // Renderer else
	} // Window else
	return open;
}

void ScreenWindow::close()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}
#pragma endregion

#pragma region Core Functions

SDL_Surface *ScreenWindow::loadSurface(std::string path)
{
	SDL_Surface *optimizedSurface = NULL;

	SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
		printf("Failed to load BMP: %s! SDL_Error: %s.\n", path.c_str(), SDL_GetError());
	else
	{
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
			printf("Failed to optmize surface: %s! SDL_Error: %s.\n", path.c_str(), IMG_GetError());
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

SDL_Texture *ScreenWindow::loadTexture(std::string path)
{
	SDL_Texture *newTexture = NULL;
	
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
		printf("Failed to load Texture image: %s! SDL_Image_Error: %s.\n", path.c_str(), IMG_GetError());
	else
	{
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
			printf("Failed to create texture from: %s! SDL_Error: %s.\n", path.c_str(), SDL_GetError());
		SDL_FreeSurface(loadedSurface);

	}
	return newTexture;
}
#pragma endregion