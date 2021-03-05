#pragma once
#include "Core/Input.h"
#include <SDL.h>
#include <unordered_map>
#include <EventSystem/Event.h>
#include <EventSystem/KeyEvent.h>

/// <summary>
/// Creates a reference to a member function
/// </summary>
/// <param name="x">The function</param>
/// <param name="y">The instance of the class</param>
#define CreateFunctionCallback(x, y) std::bind(&x, y, std::placeholders::_1)

class Input {
	using EventCallbackFunc = std::function<void(Event&)>;

public:

	Input() {
		inputCallbacks.reserve(10);
	}

	static Input* Init();

	static bool GetKeyDown(SDL_Scancode);
	static bool GetKeyUp(SDL_Scancode);
	static bool GetKey(SDL_Scancode);

	void Listen(float deltaTime);
	void Reset();

	/// <summary>
	/// Warning: Same function can be added several times.
	/// </summary>
	void AddCallback(const EventCallbackFunc& callback);

	/// <summary>
	/// Nothing happens if you try to remove the same method twice.
	/// </summary>
	void RemoveCallback(const EventCallbackFunc& callback);


	/// <summary>
	/// Warning: Same function can be added several times.
	/// </summary>
	inline static void AddInputCallback(const EventCallbackFunc& callback, SDL_Scancode keyCode) {
		instance->inputCallbacks[keyCode].emplace_back(callback);
	}
	/// <summary>
	/// Nothing happens if you try to remove the same method twice.
	/// </summary>
	inline static void RemoveInputCallback(const EventCallbackFunc& callback, SDL_Scancode keyCode) {
		for (int i = 0; i < instance->inputCallbacks[keyCode].size(); i++) {
			CallbackData cd = instance->inputCallbacks[keyCode][i];
			if (cd.EventCallback.target_type().hash_code() == callback.target_type().hash_code()) {
				//std::cout << "callback found" << std::endl;
				instance->inputCallbacks[keyCode].erase(instance->inputCallbacks[keyCode].begin() + i);
				return;
			}
		}
	}

private:

	static Input* instance;
	float deltaTime;

	SDL_Event e { };

	const Uint8* keyStates;
	std::unordered_map<SDL_Scancode, int> keyStateFrameCount;
	std::unordered_map<SDL_Scancode, bool> wasKeyUp;

	void KeyUp();
	void KeyDown();

private: //Event System

	struct CallbackData {
		CallbackData() { }
		CallbackData(EventCallbackFunc callback): EventCallback(callback) { }

		EventCallbackFunc EventCallback;
	};

	std::unordered_map<SDL_Scancode, std::vector<CallbackData>> inputCallbacks;

	std::vector<CallbackData> callbacks;

	void SendKeyCallbacks();

	void FireEvent(Event& event, CallbackData data);
	void FireEvent(Event& e);

};