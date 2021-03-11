#include "HighScoreState.h"
#include "MainMenuState.h"

void HighScoreState::OnEnter() {
	Input::AddInputCallback(BindFunction(HighScoreState::OnEvent, this), SDL_SCANCODE_DOWN);
	Input::AddInputCallback(BindFunction(HighScoreState::OnEvent, this), SDL_SCANCODE_UP);

	GameObject* canvasGO = new GameObject();
	canvas = canvasGO->AddComponent<Canvas>();

	Text* pos1Text = UIFactory::CreateText("1: ", {255, 255, 255, 255}, 64);
	Text* pos2Text = UIFactory::CreateText("2: ", {255, 255, 255, 255}, 64);
	Text* pos3Text = UIFactory::CreateText("3: ", {255, 255, 255, 255}, 64);
	Text* pos4Text = UIFactory::CreateText("4: ", {255, 255, 255, 255}, 64);
	Text* pos5Text = UIFactory::CreateText("5: ", {255, 255, 255, 255}, 64);

	pos1Text->SetPosition(300, 40);
	pos2Text->SetPosition(300, 90);
	pos3Text->SetPosition(300, 140);
	pos4Text->SetPosition(300, 190);
	pos5Text->SetPosition(300, 240);

	texts.push_back(pos1Text);
	canvas->AddUIElement(pos1Text);
	texts.push_back(pos2Text);
	canvas->AddUIElement(pos2Text);
	texts.push_back(pos3Text);
	canvas->AddUIElement(pos3Text);
	texts.push_back(pos4Text);
	canvas->AddUIElement(pos4Text);
	texts.push_back(pos5Text);
	canvas->AddUIElement(pos5Text);

	Text* text = UIFactory::CreateText("<-- Back", {255, 255, 255, 255}, 64);
	Button* backButton = UIFactory::CreateButton("Assets/Sprites/buttonBackgroundNormal.png", "Assets/Sprites/buttonBackgroundSelected.png", Vector2(300, 435), text, BindFunction(HighScoreState::MainMenu, this));

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

void HighScoreState::OnUpdate(float deltaTime) { }

void HighScoreState::OnExit() {
	Input::RemoveInputCallback(BindFunction(HighScoreState::OnEvent, this), SDL_SCANCODE_DOWN);
	Input::RemoveInputCallback(BindFunction(HighScoreState::OnEvent, this), SDL_SCANCODE_UP);
	GameObject::Destroy(canvas->gameObject);
}

//void HighScore::AddCallback(const EventCallbackFunc& callback) {
//	onChangeState.EventCallback = callback;
//}
//
//void HighScore::RemoveCallback(const EventCallbackFunc& callback) {
//	onChangeState.EventCallback = nullptr;
//}

void HighScoreState::OnEvent(Event& event) {
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<KeyPressedEvent>(BindFunction(HighScoreState::OnKeyPressedEvent, this));
}

bool HighScoreState::OnKeyPressedEvent(KeyPressedEvent& e) {
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

void HighScoreState::MainMenu(void*) {
	SoundCoordinator::PlayEffect("Assets/SoundFx/menuEnter2.wav");
	gameInstance->ChangeToState<MainMenuState>();
}

/*oid HighScore::FireEvent(Event& event) {
	SoundCoordinator::PlayEffect("Assets/SoundFx/menuEnter2.wav");
	onChangeState.EventCallback(event);
}*/