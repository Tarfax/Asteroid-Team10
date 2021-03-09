#pragma once

#include <stdio.h>
#include <SDL.h>
#include <iostream>
#include <string>

#include "Objects/GameObject.h"
#include "Time.h"
#include "Core/Input.h"
#include <EventSystem/EngineEvent.h>
#include "ObjectPool.h"

#include <Core/GameState.h>
#include <Component/ParticleSystem.h>
#include <Component/Core/Renderer.h>



const int SCREEN_WIDTH {640};
const int SCREEN_HEIGHT {480};

class Engine {
public:
	Engine();
	
	bool Init();

	void Run();

	void Quit();

private:
	void Update();
	void Render();

	void SetupEventSystem();

	/// <summary>
	/// 
	/// </summary>

	void OnEvent(Event& e);
	bool OnWindowClose(EngineCloseEvent& e);


	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Surface* image;

	GameState* gameState;
	Input* input;
	GameObject* gameObject;


	Time* time;

	ParticleSystem* particleSystem;

	bool isRunning;
};
