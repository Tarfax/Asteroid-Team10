#include "Engine.h"

#include <iostream>
#include <string>

#include <Core/Time.h>
#include <Core/Input.h>
#include <Core/Physics.h>
#include <Core/GameInstance.h>

#include <FactorySystem/PredefinedObject.h>
#include <EventSystem/EngineEvent.h>
#include <Component/Core/Renderer.h>


Engine::Engine() { }

bool Engine::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL could not SDL_Init()! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow("Asteroids - by Team 10", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		std::cout << "SDL could not SDL_CreateWindow()! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cout << "SDL could not SDL_CreateRenderer()! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);

	time = new Time();
	input = Input::Init();
	physics = Physics::Init(SCREEN_WIDTH, SCREEN_HEIGHT);

	TextureCoordinator::Init(renderer);
	PredefinedObject::Init();
	SoundCoordinator::Init();

	gameInstance = new GameInstance();
	gameInstance->Init();

	SetupEventSystem();

	return true;
}

void Engine::Run() {
	isRunning = true;

	while (isRunning == true) {
		time->StartTick();

		input->Listen(time->GetDeltaTime());

		GameObject::Init();
		GameObject::Enable();

		physics->CheckCollisions();

		gameInstance->Update(time->GetDeltaTime());
		physics->UpdateColliders();

		Render();

		GameObject::Disable();
		GameObject::CleanUp();

		time->EndTick();
	}
}

void Engine::Render() {
	//Clear the display
	SDL_RenderClear(renderer);

	//Render all the objects
	Renderer::Draw(renderer);
	GameObject::Draw(renderer);

	//Background color
	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);

	//Render to screen
	SDL_RenderPresent(renderer);
}

void Engine::Quit() {

	gameInstance->Destroy();
	physics->Destroy();
	SoundCoordinator::Destroy();
	TextureCoordinator::Destroy();
	PredefinedObject::Destroy();
	input->Destroy();

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_Quit();
}

void Engine::SetupEventSystem() {
	input->AddCallback(BindFunction(Engine::OnEvent, this));
}


void Engine::OnEvent(Event& e) {
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<EngineCloseEvent>(BindFunction(Engine::OnWindowClose, this));
}

bool Engine::OnWindowClose(EngineCloseEvent& e) {
	std::cout << "\n -- Quit and Clean Up --\n\n";
	isRunning = false;
	input->RemoveCallback(BindFunction(Engine::OnEvent, this));
	return true;
}