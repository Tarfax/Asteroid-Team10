#include "MainMenu.h"
#include "SoundSystem/SoundCoordinator.h"

void MainMenu::Init() {
	Input::AddInputCallback(BindFunction(MainMenu::OnEvent, this), SDL_SCANCODE_DOWN);
	Input::AddInputCallback(BindFunction(MainMenu::OnEvent, this), SDL_SCANCODE_UP);

	GameObject* canvasGO = new GameObject();
	canvas = canvasGO->AddComponent<Canvas>();

	Text* text = CreateText("Start Game", {255, 255, 255, 255}, 64);
	CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 35), text, BindFunction(MainMenu::StartGame, this));

	Text* text2 = CreateText("Settings", {255, 255, 255, 255}, 64);
	CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 135), text2, BindFunction(MainMenu::Settings, this));

	Text* text3 = CreateText("Credits", {255, 255, 255, 255}, 64);
	CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 235), text3, BindFunction(MainMenu::Credits, this));

	Text* text4 = CreateText("High Score", {255, 255, 255, 255}, 64);
	CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 335), text4, BindFunction(MainMenu::HighScore, this));

	Text* text5 = CreateText("Quit Game", {255, 255, 255, 255}, 64);
	CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 435), text5, BindFunction(MainMenu::QuitGame, this));

	selectionImage = new Image("Assets/Sprites/ship.png");
	selectionImage->Init();
	selectionImage->SetPosition(Vector2(0, 35));
	canvas->AddUIElement(selectionImage);

	buttons[currentSelectedElement]->SetState(ButtonState::Selected);
	SDL_Rect position = buttons[currentSelectedElement]->GetPosition();
	selectionImage->SetPosition(position.x - selectionImage->GetPosition().w - 15, position.y + position.h / 2 - selectionImage->GetPosition().h / 2);
}

Text* MainMenu::CreateText(std::string msg, SDL_Color color, int size) {

	Text* text = new Text(msg, color, size);
	text->Init();
	texts.push_back(text);
	canvas->AddUIElement(text);
	return text;
}

Button* MainMenu::CreateButton(std::string normal, std::string selected, Vector2 position, Text* text, ButtonCallback cb) {

	Button* button = new Button(normal, selected, cb);
	button->Init();
	button->SetPosition(position);
	button->SetText(text);
	buttons.push_back(button);
	canvas->AddUIElement(button);

	return button;
}

void MainMenu::Update(float deltaTime) {

}

void MainMenu::Destroy() {
	Input::RemoveInputCallback(BindFunction(MainMenu::OnEvent, this), SDL_SCANCODE_DOWN);
	Input::RemoveInputCallback(BindFunction(MainMenu::OnEvent, this), SDL_SCANCODE_UP);
	GameObject::Destroy(canvas->gameObject);
}

void MainMenu::AddCallback(const EventCallbackFunc& callback) {
	menuButtonPressed.EventCallback = callback;
}

void MainMenu::RemoveCallback(const EventCallbackFunc& callback) {
	menuButtonPressed.EventCallback = nullptr;
}

void MainMenu::OnEvent(Event& event) {
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<KeyPressedEvent>(BindFunction(MainMenu::OnKeyPressedEvent, this));
}

bool MainMenu::OnKeyPressedEvent(KeyPressedEvent& e) {
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

void MainMenu::StartGame(void*) {
	MenuStartGameEvent e(this);
	FireEvent(e);
}

void MainMenu::Settings(void*) {
	MenuSettingsEvent e(this);
	FireEvent(e);
}

void MainMenu::Credits(void*) {
	MenuCreditsEvent e(this);
	FireEvent(e);
}

void MainMenu::HighScore(void*) {
	MenuHighScoreEvent e(this);
	FireEvent(e);
}

void MainMenu::QuitGame(void*) {
	MenuQuitGameEvent e(this);
	FireEvent(e);
}

void MainMenu::FireEvent(Event& event) {
	SoundCoordinator::PlayEffect("Assets/SoundFx/menuEnter2.wav");
	menuButtonPressed.EventCallback(event);
}
