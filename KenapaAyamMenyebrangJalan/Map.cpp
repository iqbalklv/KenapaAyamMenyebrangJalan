#include "Map.h"
#include "TextureManager.h"

int lvlDef[Map::row][Map::column] = {
{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
{ 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0 },
{ 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 },
{ 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0 },
{ 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 },
{ 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0 },
{ 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 },
{ 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0 },
{ 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 },
{ 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0 },
{ 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 },
{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
};

Map::Map() {
	grass = TextureManager::LoadTexture("assets/grass.png");
	grass2 = TextureManager::LoadTexture("assets/grass2.png");
	border = TextureManager::LoadTexture("assets/border.png");

	LoadMap(lvlDef);

	src.x = src.y = 0;
	src.w = dest.w = src.h = dest.h = TextureManager::size;
	
	dest.x = dest.y = 0;
}

Map::~Map() {
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(border);
	SDL_DestroyTexture(grass2);
}

void Map::LoadMap(int arr[row][column]) {
	for (int row = 0; row < Map::row; row++)
	{
		for (int col = 0; col < column; col++)
		{
			map[row][col] = arr[row][col];
		}
	}
}

void Map::DrawMap() {

	int type = 0;

	for (int row = 0; row < Map::row; row++)
	{
		for (int col = 0; col < column; col++)
		{
			type = map[row][col];

			dest.x = col * TextureManager::size;
			dest.y = row * TextureManager::size;

			switch (type) {
				case 0:
					TextureManager::Draw(grass, src, dest);
					break;
				case 1:
					TextureManager::Draw(grass2, src, dest);
					break;
				case 2:
					TextureManager::Draw(border, src, dest);
					break;
				default:
					break;
			}
		}
	}
}