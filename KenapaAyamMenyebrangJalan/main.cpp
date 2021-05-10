#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[]) {
	const float targetFrameRate = 60;
	const float targetFrameTime = 1000 / targetFrameRate;
	
	Uint32 frameStart, frameTime;
	
	game = new Game();

	game->init("Kenapa Ayam Menyebrang Jalan?", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);


	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();


		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < targetFrameTime) {
			SDL_Delay((float)targetFrameTime - frameTime);
		}
	}

	game->clean();

	return 0;
}