/*	TODO LIST:
 *	Implement:
 *				-Render textures on Screen = SDL_RendererCopy
 *				-Clear Screen = SDL_RendererClear
 *				-Update Screen = SDL_Present
 */

#pragma once
#ifndef SCREEN_WINDOW_H
#define SCREEN_WINDOW_H

#include <SDL.h>
#include <SDL_image.h>

#include <stdlib.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class ScreenWindow
{
public:
	inline static ScreenWindow &Instance()
	{
		static ScreenWindow inst;
		return inst;
	}
	~ScreenWindow();

private:
	ScreenWindow();

	SDL_Window *gWindow = NULL;
	SDL_Surface *gScreenSurface = NULL;
	SDL_Surface *gCurrentSurface = NULL;
	
	SDL_Renderer *gRenderer = NULL;
	SDL_Texture *gTexture = NULL;
	Viewport view = Viewport();
	
	bool init();
	void close();

public:
	SDL_Surface *loadSurface(std::string);
	SDL_Texture *loadTexture(std::string);

	//Singleton extra... DO NOT IMPLEMENT!
	ScreenWindow(ScreenWindow const &r) = delete;
	void operator=(ScreenWindow const &r) = delete;
};

struct Viewport
{
	SDL_Rect v;
	void SetViewPort(int x, int y, int w, int h) {
		v.x = x;
		v.y = y;
		v.w = w;
		v.h = h;
	}
	Viewport()
	{
		SetViewPort(1, 1, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
};
#endif