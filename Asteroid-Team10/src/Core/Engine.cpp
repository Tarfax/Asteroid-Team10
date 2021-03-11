#include "Engine.h"
#include "FactorySystem/Factory.h"
#include "PlayerController.h"
#include "TextureCoordinator.h"
#include "SoundSystem/SoundCoordinator.h"
#include "Component/Asteroid.h"
#include <string>
#include <iostream>
#include <Structs/Vector2.h>
#include <Math/Mathf.h>

#include <FactorySystem/Predef.h>
#include <FactorySystem/Factory.h>


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
	PredefinedObject::Init();
	SoundCoordinator::Init();

	//objectPool = ObjectPool::GetInstance();
	//objectPool->Init();
	ObjectPool::Init();

	gameInstance = new GameInstance();
	gameInstance->Init();

	SetupEventSystem();

	//SoundCoordinator::LoadEffect("Assets/SoundFx/fire4.wav");
	//SoundCoordinator::LoadEffect("Assets/SoundFx/explosion.wav");
	//SoundCoordinator::LoadEffect("Assets/SoundFx/engine.wav");
	//gameObject = PlayerController::GetInstance();
	
	//objectPool->SetPoolSize(ProjectilePool, 30);
	//Factory::GetInstance<Asteroid>(Predef::Asteroid_Lvl1);

	//particleSystem = ParticleSystem::GetInstance()->GetComponent<ParticleSystem>();

	return true;
}

void Engine::Run() {
	isRunning = true;

	while (isRunning == true) {
		time->StartTick();

		input->Listen(time->GetDeltaTime());

		GameObject::Init();
		GameObject::Enable();

		Update();
		gameInstance->Update(time->GetDeltaTime());
		Render();

		GameObject::Disable();
		GameObject::CleanUp();

		time->EndTick();
	}
	Quit();
}

void Engine::Update() {
	GameObject::Update(time->GetDeltaTime());

	//particleSystem->OnUpdate(time->GetDeltaTime());
}

void Engine::Render() {
	//Clear the display
	SDL_RenderClear(renderer);

	//Render all the objects
	Renderer::Draw(renderer);
	GameObject::Draw(renderer);
	//particleSystem->Draw(renderer);

	//Background color
	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);

	//Render to screen
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

void Engine::SetupEventSystem() {
	//input->RemoveCallback(BindFunction(Engine::OnEvent, this), SDL_SCANCODE_F);
	input->AddCallback(BindFunction(Engine::OnEvent, this));
	
}


void Engine::OnEvent(Event& e) {
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<EngineCloseEvent>(BindFunction(Engine::OnWindowClose, this));
}

bool Engine::OnWindowClose(EngineCloseEvent& e) {
	std::cout << "Don't you fucking quit on me!!\n";
	isRunning = false;
	return true;
}

