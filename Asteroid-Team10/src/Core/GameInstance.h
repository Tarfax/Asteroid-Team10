#pragma once

//#include <EventSystem/ObjectEvent.h>
//#include <EventSystem/MenuEvent.h>
//#include "PlayerController.h"
#include <FSM/GameState.h>
#include <functional>
#include <iostream>

class GameState;
class GameInstance {
	using CallbackNextFrame = std::function<void(void*)>;
public:
	GameInstance();
	void Init();
	void Update(float deltaTime);
	void Destroy();

	template <typename T, typename = std::enable_if_t<std::is_base_of<GameState, T>::value>>
	inline void ChangeToState() {
		switchToNewState = true;

		newState = new T();
		if (newState == nullptr) {
			std::cout << "Why null?" << std::endl;
		}

		std::cout << "ChangeToState::newState " << newState->ToString() << std::endl << std::endl;
	}

private: 

	void SwitchState();
	//void OnEvent(Event& e);
	//bool OnAsteroidDestroyed(AsteroidDestroyedEvent& e);
	//bool OnMenuQuitGameEvent(MenuQuitGameEvent& e);
	//bool OnMenuStartGameEvent(MenuStartGameEvent& e);

	//void CreateLevel(int level);

	//void QuitGame(void*);
	//void StartGame(void*);
	//void CreatePlayer(void*);
	//void CreateFirstLevel(void*);

	//void CreateMainMenu();
	//void DestroyMainMenu();

	/*bool callFunctionNextFrame = false;
	CallbackNextFrame callback;

	Transform* playerTransform;

	int asteroidsInPlay = 0;

	MainMenuState* mainMenu;

	int currentLevel;

	float time = 2.0f;
	float timer;*/

	bool switchToNewState;
	GameState* state;
	GameState* newState;

};

