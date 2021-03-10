#pragma once

#include <EventSystem/ObjectEvent.h>
#include <EventSystem/MenuEvent.h>
#include "PlayerController.h"
#include <UI/MainMenu.h>

class GameState {
	using CallbackNextFrame = std::function<void(void*)>;
public:
	GameState();
	void Init();
	void Update(float deltaTime);

private: 
	void OnEvent(Event& e);
	bool OnAsteroidDestroyed(AsteroidDestroyedEvent& e);
	bool OnMenuQuitGameEvent(MenuQuitGameEvent& e);
	bool OnMenuStartGameEvent(MenuStartGameEvent& e);

	void Level01();

	void QuitGame(void*);
	void StartGame(void*);

	void CreateMainMenu();
	void DestroyMainMenu();

	bool callFunctionNextFrame = false;
	CallbackNextFrame callback;

	Transform* playerTransform;

	int asteroidsInPlay = 0;

	MainMenu* mainMenu;


	float time = 2.0f;
	float timer;
};