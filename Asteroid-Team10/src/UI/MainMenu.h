#pragma once

#include <Component/Core/SpriteRenderer.h>
#include <FactorySystem/FactoryObject.h>
#include <Component/Behaviour/Behaviour.h>
#include <Component/Core/Canvas.h>
#include <UI/Button.h>
#include <UI/Image.h>
#include <UI/Text.h>
#include <Core/Input.h>
#include <EventSystem/MenuEvent.h>

class MainMenu {
	using ButtonCallback = std::function<void(void*)>;
	using EventCallbackFunc = std::function<void(Event&)>;

public:
	MainMenu() { }
	~MainMenu() {
		std::cout << "Main menu gone" << std::endl;
	}
	void Init()	;
	void Update(float deltaTime) ;
	void Destroy() ;

	/// <summary>
	/// Warning: Same function can be added several times.
	/// </summary>
	void AddCallback(const EventCallbackFunc& callback);

	/// <summary>
	/// Nothing happens if you try to remove the same method twice.
	/// </summary>
	void RemoveCallback(const EventCallbackFunc& callback);

private:
	Button* CreateButton(std::string normal, std::string selected, Vector2 position, Text* text, ButtonCallback cb);
	Text* CreateText(std::string msg, SDL_Color color, int size);

	void OnEvent(Event& event);
	bool OnKeyPressedEvent(KeyPressedEvent& e);

	void StartGame(void*);
	void Settings(void*);
	void Credits(void*);
	void HighScore(void*);
	void QuitGame(void*);

	void FireEvent(Event& event);

	struct CallbackData {
		CallbackData() { }
		CallbackData(EventCallbackFunc callback): EventCallback(callback) { }

		EventCallbackFunc EventCallback;
	};

	CallbackData menuButtonPressed;

	int currentSelectedElement = 0;

	std::vector<Button*> buttons;
	std::vector<Text*> texts;
	Image* selectionImage;

	SpriteRenderer* renderer;
	Canvas* canvas;


};