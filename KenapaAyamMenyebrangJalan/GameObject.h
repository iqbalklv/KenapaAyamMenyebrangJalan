#pragma once
#include "Game.h"

class GameObject {

public:
	GameObject(const char* texturesheet, int xpos, int ypos);
	~GameObject();

	void Update();
	void Render();
	
private:
	int x;
	int y;

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};