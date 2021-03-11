#pragma once
#include <FSM/GameState.h>

class SettingsState: public GameState {
public:
	void OnEnter() override;
	void OnUpdate(float deltaTime) override;
	void OnExit() override;

};