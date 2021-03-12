#include <FSM/MainMenuState.h>

#include <FSM/QuitGameState.h>
#include <FSM/HighScoreState.h>
#include <FSM/GamePlayState.h>
#include <FSM/SettingsState.h>
#include <FSM/CreditsState.h>

void MainMenuState::OnEnter() {
	Input::AddInputCallback(BindFunction(MainMenuState::OnEvent, this), SDL_SCANCODE_DOWN);
	Input::AddInputCallback(BindFunction(MainMenuState::OnEvent, this), SDL_SCANCODE_UP);

	GameObject* canvasGO = new GameObject();
	canvas = canvasGO->AddComponent<Canvas>();

	Text* startGame = UIFactory::CreateText("Start Game", {255, 255, 255, 255}, 64);
	Button* startGameButton = UIFactory::CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 35), startGame, BindFunction(MainMenuState::StartGame, this));

	texts.push_back(startGame);
	canvas->AddUIElement(startGame);
	buttons.push_back(startGameButton);
	canvas->AddUIElement(startGameButton);

	Text* settings = UIFactory::CreateText("Settings", {255, 255, 255, 255}, 64);
	Button* settingsButton = UIFactory::CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 135), settings, BindFunction(MainMenuState::Settings, this));

	texts.push_back(settings);
	canvas->AddUIElement(settings);
	buttons.push_back(settingsButton);
	canvas->AddUIElement(settingsButton);

	Text* credits = UIFactory::CreateText("Credits", {255, 255, 255, 255}, 64);
	Button* creditsButton = UIFactory::CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 235), credits, BindFunction(MainMenuState::Credits, this));

	texts.push_back(credits);
	canvas->AddUIElement(credits);
	buttons.push_back(creditsButton);
	canvas->AddUIElement(creditsButton);

	Text* highScore = UIFactory::CreateText("High Score", {255, 255, 255, 255}, 64);
	Button* highScoreButton = UIFactory::CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 335), highScore, BindFunction(MainMenuState::HighScore, this));

	texts.push_back(highScore);
	canvas->AddUIElement(highScore);
	buttons.push_back(highScoreButton);
	canvas->AddUIElement(highScoreButton);

	Text* quitGame = UIFactory::CreateText("Quit Game", {255, 255, 255, 255}, 64);
	Button* quitGameButton = UIFactory::CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 435), quitGame, BindFunction(MainMenuState::QuitGame, this));

	texts.push_back(quitGame);
	canvas->AddUIElement(quitGame);
	buttons.push_back(quitGameButton);
	canvas->AddUIElement(quitGameButton);

	selectionImage = new Image("Assets/Sprites/ship.png");
	selectionImage->Init();
	selectionImage->SetPosition(Vector2(0, 35));
	canvas->AddUIElement(selectionImage);

	buttons[currentSelectedElement]->SetState(ButtonState::Selected);
	SDL_Rect position = buttons[currentSelectedElement]->GetPosition();
	selectionImage->SetPosition(position.x - selectionImage->GetPosition().w - 15, position.y + position.h / 2 - selectionImage->GetPosition().h / 2);
}

void MainMenuState::OnUpdate(float deltaTime) {

}

void MainMenuState::OnExit() {
	Input::RemoveInputCallback(BindFunction(MainMenuState::OnEvent, this), SDL_SCANCODE_DOWN);
	Input::RemoveInputCallback(BindFunction(MainMenuState::OnEvent, this), SDL_SCANCODE_UP);
	GameObject::Destroy(canvas->gameObject, Predef::Unknown);
}

void MainMenuState::AddCallback(const EventCallbackFunc& callback) {
	onChangeState.EventCallback = callback;
}

void MainMenuState::RemoveCallback(const EventCallbackFunc& callback) {
	onChangeState.EventCallback = nullptr;
}

void MainMenuState::OnEvent(Event& event) {
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<KeyPressedEvent>(BindFunction(MainMenuState::OnKeyPressedEvent, this));
}

bool MainMenuState::OnKeyPressedEvent(KeyPressedEvent& e) {
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

void MainMenuState::StartGame(void*) {
	SoundCoordinator::PlayEffect("Assets/SoundFx/menuEnter2.wav");
	gameInstance->ChangeToState<GamePlayState>();

}

void MainMenuState::Settings(void*) {
	SoundCoordinator::PlayEffect("Assets/SoundFx/menuEnter2.wav");
	//gameInstance->ChangeToState<SettingsState>();

}

void MainMenuState::Credits(void*) {
	SoundCoordinator::PlayEffect("Assets/SoundFx/menuEnter2.wav");
	gameInstance->ChangeToState<CreditsState>();

}

void MainMenuState::HighScore(void*) {
	SoundCoordinator::PlayEffect("Assets/SoundFx/menuEnter2.wav");
	gameInstance->ChangeToState<HighScoreState>();
}

void MainMenuState::QuitGame(void*) {
	SoundCoordinator::PlayEffect("Assets/SoundFx/menuEnter2.wav");
	//gameInstance->ChangeToState<QuitGameState>();
}
