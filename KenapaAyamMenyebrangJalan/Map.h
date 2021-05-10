#pragma once
#include "Game.h"

class Map {

public:
	const static int row = 12;
	const static int column = 20;

	Map();
	~Map();

	void LoadMap(int arr[row][column]);
	void DrawMap();

	

private:

	SDL_Rect src, dest;
	SDL_Texture* grass;
	SDL_Texture* grass2;
	SDL_Texture* border;

	int map[row][column];


};