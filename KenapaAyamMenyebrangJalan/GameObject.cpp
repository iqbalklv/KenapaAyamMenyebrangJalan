#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int xpos, int ypos) {
	
	texture = TextureManager::LoadTexture(texturesheet);

	x = xpos;
	y = ypos;
}

void GameObject::Update() {

	float mult = 1;

	x++;
	y++;

	srcRect.h = srcRect.w = TextureManager::size;
	srcRect.x = srcRect.y = 0;

	destRect.x = x;
	destRect.y = y;
	destRect.h = srcRect.h * mult;
	destRect.w = srcRect.w * mult;
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}