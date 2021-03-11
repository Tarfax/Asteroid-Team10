#pragma once
#include <FSM/GameState.h>
#include <Core/GameInstance.h>

class CreditsState: public GameState {
public:
	void OnEnter() override;
	void OnUpdate(float deltaTime) override;
	void OnExit() override;

	std::string ToString() {
		return "CreditsState";
	};

	void OnEvent(Event& event);
	bool OnKeyPressedEvent(KeyPressedEvent& e);

	void MainMenu(void*);

	int currentSelectedElement = 0;

	std::vector<Button*> buttons;
	std::vector<Text*> texts;
	Image* selectionImage;

	Canvas* canvas;
};