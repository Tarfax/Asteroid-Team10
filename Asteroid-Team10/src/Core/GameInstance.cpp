#include "GameInstance.h"
#include <FSM/MainMenuState.h>

GameInstance::GameInstance() { }

void GameInstance::Init() {
	ChangeToState<MainMenuState>();
}

void GameInstance::Update(float deltaTime) {
	if (switchToNewState == true) {
		SwitchState();
		switchToNewState = false;
	}

	state->Update(deltaTime);
}

void GameInstance::Destroy() {
	state->Exit();
	delete state;
	state = nullptr;
}

void GameInstance::SwitchState() {
	if (state != nullptr) {
		state->Exit();
	}
	delete state;
	state = newState;
	state->Enter(this);
	newState = nullptr;
}
