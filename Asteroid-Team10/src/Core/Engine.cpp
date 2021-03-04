#include "Engine.h"
#include "PlayerController.h"
#include "TextureCoordinator.h"
#include "Component/Asteroid.h"
#include <string>
#include <iostream>
#include <Structs/Vector2.h>
#include <Math/Mathf.h>

Engine::Engine() { }

bool Engine::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not SDL_Init()! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Asteroids - by Team 10", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		printf("SDL could not SDL_CreateWindow()! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		printf("SDL could not SDL_CreateRenderer()! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);

	time = new Time();

	input = Input::Init();

	TextureCoordinator::Init(renderer);

	gameObject = PlayerController::CreateInstance();

	PlayerController* pc = gameObject->GetComponent<PlayerController>();

	asteroid = Asteroid::GetInstance();

	asteroid->GetComponent<Asteroid>()->SetActive(true);
	asteroid->GetComponent<Asteroid>()->SetActive(true);
	asteroid->GetComponent<Asteroid>()->SetActive(false);
	asteroid->GetComponent<Asteroid>()->SetActive(false);

	asteroid2 = Asteroid::GetInstance();

	asteroid2->GetComponent<Asteroid>()->SetActive(true);
	asteroid2->GetComponent<Asteroid>()->SetActive(true);
	asteroid2->GetComponent<Asteroid>()->SetActive(false);
	asteroid2->GetComponent<Asteroid>()->SetActive(false);

	return true;
}

void Engine::Run() {
	isRunning = true;
	while (isRunning == true) {
		time->StartTick();
		input->Listen();

		Update();
		Render();
		GameObject::CleanUp();

		input->Reset();
		time->EndTick();

		if (input->hasQuitBeenCalled == true) {
			isRunning = false;
		}
	}
	Quit();
}

void Engine::Update() {
	GameObject::DoUpdate(time->GetDeltaTime());
}

void Engine::Render() {
	SDL_RenderClear(renderer);

	// TODO: Get what's supposed to be rendering
	// Renderer::RenderYourShit();

	GameObject::DoDraw(renderer);

	//Background color
	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);

	SDL_RenderPresent(renderer);
}

void Engine::Quit() {

	// TODO:
	//
	// Clean up all the game objects?
	//

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_Quit();
}
