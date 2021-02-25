#include "Engine.h"
#include "PlayerController.h"
#include "TextureCoordinator.h"
#include <string>
#include <iostream>
#include <Structs/Vector2.h>

Engine::Engine() { }

bool Engine::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not SDL_Init()! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Asteroids - by Team 10", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		printf("SDL could not SDL_CreateWindow()! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL) {
		printf("SDL could not SDL_CreateRenderer()! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);

	if (LoadMedia("Assets/Sprites/CoolImage.bmp") == false) {
		printf("Unable to load image %s! SDL Error: %s\n", "CoolImage.bmp", SDL_GetError());
		return false;
	}

	time = new Time();

	TextureCoordinator::Init(renderer);

	gameObject = new GameObject();
	gameObject->Init();

	Vector2 a;
	Vector2 b;
	Vector2 c;

	//c = a + b;

	return true;
}

void Engine::Run() {
	isRunning = true;

	while (isRunning == true) {
		time->StartTick();
		Input();
		Update();
		Render();
		time->EndTick();
		//std::cout << "deltaTime: " << std::to_string(time->GetDeltaTime()) << std::endl;
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
	gameObject->Update(time->GetDeltaTime());
}

void Engine::Render() {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);

	// TODO: Get what's supposed to be rendering
	// Renderer::RenderYourShit();
	gameObject->Draw(renderer);

	SDL_RenderPresent(renderer);
}

bool Engine::LoadMedia(std::string path) {
	image = SDL_LoadBMP(path.c_str());

	if (image == NULL) {
		return false;
	}

	PlayerController::Instance();

	return true;
}

void Engine::Close() {
	gameObject->Destroy();
	delete gameObject;

	SDL_FreeSurface(image);
	image = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_Quit();
}
