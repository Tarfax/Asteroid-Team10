#include "PauseMenu.h"
#include "SoundSystem/SoundCoordinator.h"
#include <UI/UIFactory.h>

void PauseMenu::Init() {
	Input::AddInputCallback(BindFunction(PauseMenu::OnEvent, this), SDL_SCANCODE_DOWN);
	Input::AddInputCallback(BindFunction(PauseMenu::OnEvent, this), SDL_SCANCODE_UP);

	GameObject* canvasGO = new GameObject();
	canvas = canvasGO->AddComponent<Canvas>();

	Text* resumeText = UIFactory::CreateText("Resume Game", {255, 255, 255, 255}, 64);
	Button* resumeButton = UIFactory::CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 235), resumeText, BindFunction(PauseMenu::ResumeGame, this));

	texts.push_back(resumeText);
	canvas->AddUIElement(resumeText);
	buttons.push_back(resumeButton);
	canvas->AddUIElement(resumeButton);

	Text* mainMenuText = UIFactory::CreateText("Main Menu", {255, 255, 255, 255}, 64);
	Button* mainMenuButton = UIFactory::CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 335), mainMenuText, BindFunction(PauseMenu::MainMenuState, this));

	texts.push_back(mainMenuText);
	canvas->AddUIElement(mainMenuText);
	buttons.push_back(mainMenuButton);
	canvas->AddUIElement(mainMenuButton);

	selectionImage = new Image("Assets/Sprites/ship.png");
	selectionImage->Init();
	selectionImage->SetPosition(Vector2(0, 35));
	canvas->AddUIElement(selectionImage);

	buttons[currentSelectedElement]->SetState(ButtonState::Selected);
	SDL_Rect position = buttons[currentSelectedElement]->GetPosition();
	selectionImage->SetPosition(position.x - selectionImage->GetPosition().w - 15, position.y + position.h / 2 - selectionImage->GetPosition().h / 2);
}

void PauseMenu::Update(float deltaTime) { }

void PauseMenu::Destroy() {
	Input::RemoveInputCallback(BindFunction(PauseMenu::OnEvent, this), SDL_SCANCODE_DOWN);
	Input::RemoveInputCallback(BindFunction(PauseMenu::OnEvent, this), SDL_SCANCODE_UP);
	GameObject::Destroy(canvas->gameObject);
}

void PauseMenu::AddCallback(const EventCallbackFunc& callback) {
	onChangeState.EventCallback = callback;
}

void PauseMenu::RemoveCallback(const EventCallbackFunc& callback) {
	onChangeState.EventCallback = nullptr;
}

void PauseMenu::OnEvent(Event& event) {
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<KeyPressedEvent>(BindFunction(PauseMenu::OnKeyPressedEvent, this));
}

bool PauseMenu::OnKeyPressedEvent(KeyPressedEvent& e) {
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

void PauseMenu::ResumeGame(void*) {
	MenuResumeGameEvent e(NULL);
	FireEvent(e);
}

void PauseMenu::MainMenuState(void*) {
	MenuMainMenuEvent e(NULL);
	FireEvent(e);
}

void PauseMenu::FireEvent(Event& event) {
	SoundCoordinator::PlayEffect("Assets/SoundFx/menuEnter2.wav");
	onChangeState.EventCallback(event);
}