#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include <cstdlib>
#include "AssetManager.h"
#include <sstream>;

Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager* Game::assets = new AssetManager(&manager);

//Entities
auto& player(manager.addEntity());
auto& enemy1(manager.addEntity());
auto& enemy2(manager.addEntity());
auto& enemy3(manager.addEntity());
auto& enemy4(manager.addEntity());
auto& enemy5(manager.addEntity());
auto& enemy6(manager.addEntity());
auto& enemy7(manager.addEntity());
auto& enemy8(manager.addEntity());
auto& enemy9(manager.addEntity());
auto& enemy10(manager.addEntity());
auto& enemy11(manager.addEntity());
auto& enemy12(manager.addEntity());
auto& enemy13(manager.addEntity());
auto& enemy14(manager.addEntity());
auto& enemy15(manager.addEntity());
auto& enemy16(manager.addEntity());
auto& enemy17(manager.addEntity());
auto& enemy18(manager.addEntity());
auto& enemy19(manager.addEntity());
auto& enemy20(manager.addEntity());

auto& levelTxt(manager.addEntity());
auto& hilevelTxt(manager.addEntity());

Entity* entities[] = { &enemy1, &enemy2, &enemy3, &enemy4, &enemy5, &enemy6, &enemy7, &enemy8, &enemy9, &enemy10, &enemy11, &enemy12, &enemy13, &enemy14, &enemy15, &enemy16, &enemy17, &enemy18, &enemy19, &enemy20 };
int entitiesSize = 20;
const float maxX = 1280.0f + 32.0f;
const float minX = -64.0f - 32.0f;
float minSpeed = 3;
float maxSpeed = 4;
int level = -1;
int hilevel = -99;
//------------------
Game::Game() {
}

Game::~Game() {
}

float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void initEntities(int level) {
	if (level == -1) {
		player.addComponent<TransformComponent>((maxX - 32) / 2.0f, 0.0f, 48, 48, 1);
		player.addComponent<SpriteComponent>("assets/chicken-1.png");
		player.addComponent<KeyboardController>();
		player.addComponent<ColliderComponent>("player");

		float xPos = 0.0f;
		int yIndex = 1;
		for (int i = 0; i < entitiesSize; i += 2)
		{

			entities[i]->addComponent<TransformComponent>(RandomFloat(minX, maxX), 64.0f * yIndex, 16, 16, 4);
			entities[i]->addComponent<SpriteComponent>("assets/enemyLeft.png");
			entities[i]->addComponent<ColliderComponent>("enemy");
			entities[i]->getComponent<TransformComponent>().speed = RandomFloat(minSpeed, maxSpeed);
			entities[i]->getComponent<TransformComponent>().velocity.x = -1;

			entities[i + 1]->addComponent<TransformComponent>(RandomFloat(minX, maxX), 64.0f * yIndex, 16, 16, 4);
			entities[i + 1]->addComponent<SpriteComponent>("assets/enemyRight.png");
			entities[i + 1]->addComponent<ColliderComponent>("enemy");
			entities[i + 1]->getComponent<TransformComponent>().speed = RandomFloat(minSpeed, maxSpeed);
			entities[i + 1]->getComponent<TransformComponent>().velocity.x = 1;

			yIndex++;
		}
	}
	else {
		std::stringstream ss;
		std::stringstream ss2;
		ss << "Level: " << (level + 1);
		levelTxt.getComponent<UILabel>().SetLabelText(ss.str(), "main");
		if (level > hilevel) {
			hilevel = level;
			ss2 << "Highest Level: " << (level + 1);
			hilevelTxt.getComponent<UILabel>().SetLabelText(ss2.str(), "main");
		}

		player.getComponent<TransformComponent>().position.x = (maxX - 32) / 2.0f;
		player.getComponent<TransformComponent>().position.y = 0.0f;

		for (int i = 0; i < entitiesSize; i ++)
		{
			entities[i]->getComponent<TransformComponent>().position.x = RandomFloat(minX, maxX);
			entities[i]->getComponent<TransformComponent>().speed = RandomFloat(minSpeed + (0.5f * level), maxSpeed + (0.55f * level));
		}

		
	}
	
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised!" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window Created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created!" << std::endl;
		}

		isRunning = true;
	}
	map = new Map();

	//ECS Implementation
	if (TTF_Init() == -1) {
		std::cout << "Error : SDL_TTF" << std::endl;
	}
	assets->AddFont("main", "assets/chargen.ttf", 32);
	SDL_Color black = { 0, 0, 0, 255 };
	levelTxt.addComponent<UILabel>(10, 10, "Level: 1", "main", black);
	hilevelTxt.addComponent<UILabel>(1280.0f - 320.0f, 10, "Highest Level: 1", "main", black);

	initEntities(level);

}

void Game::handleEvents() {
	

	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update() {

	
	manager.refresh();
	manager.update();

	for (int i = 0; i < entitiesSize; i++)
	{
		if (entities[i]->getComponent<TransformComponent>().position.x > maxX) {
			entities[i]->getComponent<TransformComponent>().position.x = minX;
		}

		if (entities[i]->getComponent<TransformComponent>().position.x < minX) {
			entities[i]->getComponent<TransformComponent>().position.x = maxX;
		}

		if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
			entities[i]->getComponent<ColliderComponent>().collider)) {
			player.getComponent<TransformComponent>().velocity * -1;
			std::cout << "Enemy Hit!" << std::endl;
			level = 0;
			initEntities(level);
		}
	}

	if (player.getComponent<TransformComponent>().position.y >= 720.0f - 32.0f) {
		if (level >= 0) {
			level++;
		}
		else {
			level += 2;
		}
		initEntities(level);
	}
	
}

void Game::render() {
	SDL_RenderClear(renderer);
	map->DrawMap();

	manager.draw();
	levelTxt.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;

}