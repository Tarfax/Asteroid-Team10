#pragma once
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
	}

private: 
	void SwitchState();

	bool switchToNewState;
	GameState* state;
	GameState* newState;
};

