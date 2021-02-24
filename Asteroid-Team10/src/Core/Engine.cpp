#include "Engine.h"

Engine::Engine() { }

bool Engine::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Asteroids - by Team 10", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);

	if (LoadMedia("Assets/Sprites/CoolImage.bmp") == false) {
		printf("Unable to load image %s! SDL Error: %s\n", "CoolImage.bmp", SDL_GetError());
		return false;
	}

	return true;
}

void Engine::Run() {

	isRunning = true;

	while (isRunning == true) {
		Input();
		Update();
		Render();
	}
}

void Engine::Input() {
	SDL_Event e { };

	while (SDL_PollEvent(&e) != 0) {

		if (e.type == SDL_QUIT) {
			isRunning = false;
		}

		else if (e.type == SDL_KEYDOWN) {

			// switch to allow further implementation of inputs.
			switch (e.key.keysym.sym) {

				case SDLK_ESCAPE:
					isRunning = false;
					break;
			}
		}
	}
}

void Engine::Update() {
	
}

void Engine::Render() {
	SDL_BlitSurface(image, NULL, screenSurface, NULL);

	SDL_UpdateWindowSurface(window);
}

bool Engine::LoadMedia(std::string path) {
	image = SDL_LoadBMP(path.c_str());

	if (image == NULL) {
		return false;
	}

	return true;
}

void Engine::Close() {
	SDL_FreeSurface(image);
	image = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}
