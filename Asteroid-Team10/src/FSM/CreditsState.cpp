#include "CreditsState.h"
#include "MainMenuState.h"

void CreditsState::OnEnter() {
	Input::AddInputCallback(BindFunction(CreditsState::OnEvent, this), SDL_SCANCODE_DOWN);
	Input::AddInputCallback(BindFunction(CreditsState::OnEvent, this), SDL_SCANCODE_UP);

	GameObject* canvasGO = new GameObject();
	canvas = canvasGO->AddComponent<Canvas>();

	Text* jupiter = UIFactory::CreateText("Jupiter Thulin", {255, 255, 255, 255}, 64);
	Text* jupiterProgrammer = UIFactory::CreateText("Programmer", {255, 255, 255, 255}, 44);
	Text* mikael = UIFactory::CreateText("Mikael Cedergren", {255, 255, 255, 255}, 64);
	Text* mikaelProgrammer = UIFactory::CreateText("Programmer", {255, 255, 255, 255}, 44);

	jupiter->SetPosition(150, 40);
	jupiterProgrammer->SetPosition(180, 100);
	mikael->SetPosition(150, 200);
	mikaelProgrammer->SetPosition(180, 260);

	texts.push_back(jupiter);
	canvas->AddUIElement(jupiter);
	texts.push_back(jupiterProgrammer);
	canvas->AddUIElement(jupiterProgrammer);
	texts.push_back(mikael);
	canvas->AddUIElement(mikael);
	texts.push_back(mikaelProgrammer);
	canvas->AddUIElement(mikaelProgrammer);

	Text* text = UIFactory::CreateText("<-- Back", {255, 255, 255, 255}, 64);
	Button* backButton = UIFactory::CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 435), text, BindFunction(CreditsState::MainMenu, this));

	texts.push_back(text);
	canvas->AddUIElement(text);
	buttons.push_back(backButton);
	canvas->AddUIElement(backButton);

	selectionImage = new Image("Assets/Sprites/ship.png");
	selectionImage->Init();
	selectionImage->SetPosition(Vector2(0, 35));
	canvas->AddUIElement(selectionImage);

	buttons[currentSelectedElement]->SetState(ButtonState::Selected);
	SDL_Rect position = buttons[currentSelectedElement]->GetPosition();
	selectionImage->SetPosition(position.x - selectionImage->GetPosition().w - 15, position.y + position.h / 2 - selectionImage->GetPosition().h / 2);
}

void CreditsState::OnUpdate(float deltaTime) { }

void CreditsState::OnExit() {
	Input::RemoveInputCallback(BindFunction(CreditsState::OnEvent, this), SDL_SCANCODE_DOWN);
	Input::RemoveInputCallback(BindFunction(CreditsState::OnEvent, this), SDL_SCANCODE_UP);
	GameObject::Destroy(canvas->gameObject);
}

void CreditsState::OnEvent(Event& event) {
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<KeyPressedEvent>(BindFunction(CreditsState::OnKeyPressedEvent, this));
}

bool CreditsState::OnKeyPressedEvent(KeyPressedEvent& e) {
	if (e.GetKeyCode() == SDL_SCANCODE_UP && e.GetRepeatCount() == 0) {
		buttons[currentSelectedElement]->SetState(ButtonState::Normal);

		currentSelectedElement--;
		if (currentSelectedElement < 0) {
			currentSelectedElement = buttons.size() - 1;
		}
		buttons[currentSelectedElement]->SetState(ButtonState::Selected);
		SDL_Rect position = buttons[currentSelectedElement]->GetPosition();
		selectionImage->SetPosition(position.x - selectionImage->GetPosition().w - 15, position.y + position.h / 2 - selectionImage->GetPosition().h / 2);
		SoundCoordinator::PlayEffect("Assets/SoundFx/menuSelection.wav");
	}

	if (e.GetKeyCode() == SDL_SCANCODE_DOWN && e.GetRepeatCount() == 0) {
		buttons[currentSelectedElement]->SetState(ButtonState::Normal);

		currentSelectedElement++;
		if (currentSelectedElement > buttons.size() - 1) {
			currentSelectedElement = 0;
		}
		buttons[currentSelectedElement]->SetState(ButtonState::Selected);
		SDL_Rect position = buttons[currentSelectedElement]->GetPosition();
		selectionImage->SetPosition(position.x - selectionImage->GetPosition().w - 15, position.y + position.h / 2 - selectionImage->GetPosition().h / 2);
		SoundCoordinator::PlayEffect("Assets/SoundFx/menuSelection.wav");
	}

	return true;
}

void CreditsState::MainMenu(void*) {
	SoundCoordinator::PlayEffect("Assets/SoundFx/menuEnter2.wav");
	MenuMainMenuEvent e(NULL);
	gameInstance->ChangeToState<MainMenuState>();
}