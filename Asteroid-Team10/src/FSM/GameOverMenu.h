#pragma once
#include <UI/Button.h>
#include <UI/Image.h>
#include <UI/Text.h>
#include <EventSystem/MenuEvent.h>
#include <Component/Core/Canvas.h>
#include <Core/Input.h>


class GameOverMenu {
	using EventCallbackFunc = std::function<void(Event&)>;

public:
	void Init(int score);
	void CreateUI();
	void Update(float deltaTime);
	void Destroy();

	/// <summary>
	/// Warning: Same function can be added several times.
	/// </summary>
	void AddCallback(const EventCallbackFunc& callback);

	/// <summary>
	/// Nothing happens if you try to remove the same method twice.
	/// </summary>
	void RemoveCallback(const EventCallbackFunc& callback);
private:
	void OnEvent(Event& event);
	bool OnKeyPressedEvent(KeyPressedEvent& e);

	void RestartGame(void*);
	void MainMenuState(void*);
	void FireEvent(Event& event);

	struct CallbackData {
		CallbackData() { }
		CallbackData(EventCallbackFunc callback): EventCallback(callback) { }

		EventCallbackFunc EventCallback;
	};

	CallbackData onChangeState;

	int currentSelectedElement = 0;
	int score;

	Text* gameOver;
	Text* scoreText;
	std::vector<Button*> buttons;
	std::vector<Text*> texts;
	Image* selectionImage;

	Canvas* canvas;
};