#include "GameOverMenu.h"
#include "SoundSystem/SoundCoordinator.h"
#include <UI/UIFactory.h>
#include <string>
#include <Core/EngineData.h>
#include <Structs/HighScore.h>

void GameOverMenu::Init(int score) {
	this->score = score;

	HighScore::SetScore(score);
	HighScore::SaveScore();

	Input::AddInputCallback(BindFunction(GameOverMenu::OnEvent, this), SDL_SCANCODE_DOWN);
	Input::AddInputCallback(BindFunction(GameOverMenu::OnEvent, this), SDL_SCANCODE_UP);

	CreateUI();

	buttons[currentSelectedElement]->SetState(ButtonState::Selected);
	SDL_Rect position = buttons[currentSelectedElement]->GetPosition();
	selectionImage->SetPosition(position.x - selectionImage->GetPosition().w - 15, position.y + position.h / 2 - selectionImage->GetPosition().h / 2);
}

void GameOverMenu::CreateUI() {
	GameObject* canvasGO = new GameObject();
	canvas = canvasGO->AddComponent<Canvas>();

	gameOver = UIFactory::CreateText("Game Over!", {255, 255, 255, 255}, 88);
	Vector2 size = gameOver->GetSprite()->Size;
	Vector2 position {Helper::GetScreenWidthMidPoint() - size.X / 2, 100};
	gameOver->SetPosition(position);
	canvas->AddUIElement(gameOver);

	scoreText = UIFactory::CreateText("Score: " + std::to_string(score), {255, 255, 255, 255}, 64);
	size = scoreText->GetSprite()->Size;
	position.Y = 165;
	scoreText->SetPosition(position);
	
	canvas->AddUIElement(scoreText);

	Text* resumeText = UIFactory::CreateText("Restart Game", {255, 255, 255, 255}, 58);
	Button* resumeButton = UIFactory::CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 235), resumeText, BindFunction(GameOverMenu::RestartGame, this));
	size = resumeButton->GetSprite()->Size;
	position.Y = 235;
	resumeButton->SetPositionAndText(position);

	texts.push_back(resumeText);
	canvas->AddUIElement(resumeText);
	buttons.push_back(resumeButton);
	canvas->AddUIElement(resumeButton);

	Text* mainMenuText = UIFactory::CreateText("Main Menu", {255, 255, 255, 255}, 64);
	Button* mainMenuButton = UIFactory::CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 335), mainMenuText, BindFunction(GameOverMenu::MainMenuState, this));
	size = mainMenuButton->GetSprite()->Size;
	position.Y = 335;
	mainMenuButton->SetPositionAndText(position);

	texts.push_back(mainMenuText);
	canvas->AddUIElement(mainMenuText);
	buttons.push_back(mainMenuButton);
	canvas->AddUIElement(mainMenuButton);

	selectionImage = new Image("Assets/Sprites/ship.png");
	selectionImage->Init();
	selectionImage->SetPosition(Vector2(0, 35));
	canvas->AddUIElement(selectionImage);
}

void GameOverMenu::Update(float deltaTime) { }

void GameOverMenu::Destroy() {
	Input::RemoveInputCallback(BindFunction(GameOverMenu::OnEvent, this), SDL_SCANCODE_DOWN);
	Input::RemoveInputCallback(BindFunction(GameOverMenu::OnEvent, this), SDL_SCANCODE_UP);
	GameObject::Destroy(canvas->gameObject, Predef::Unknown);
}

void GameOverMenu::AddCallback(const EventCallbackFunc& callback) {
	onChangeState.EventCallback = callback;

}

void GameOverMenu::RemoveCallback(const EventCallbackFunc& callback) {
	onChangeState.EventCallback = nullptr;

}

void GameOverMenu::OnEvent(Event& event) {
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<KeyPressedEvent>(BindFunction(GameOverMenu::OnKeyPressedEvent, this));
}

bool GameOverMenu::OnKeyPressedEvent(KeyPressedEvent& e) {
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

void GameOverMenu::RestartGame(void*) {
	MenuRestartGameEvent e(NULL);
	FireEvent(e);
}

void GameOverMenu::MainMenuState(void*) {
	MenuMainMenuEvent e(NULL);
	FireEvent(e);
}

void GameOverMenu::FireEvent(Event& event) {
	SoundCoordinator::PlayEffect("Assets/SoundFx/menuEnter2.wav");
	onChangeState.EventCallback(event);
}
