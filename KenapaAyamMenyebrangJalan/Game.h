#pragma once
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "AssetManager.h"

class AssetManager;
class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static AssetManager* assets;


private:
	int cnt = 0;
	bool isRunning;
	SDL_Window *window;
	float gameDeltaTime;

};