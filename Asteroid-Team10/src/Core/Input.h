#pragma once
#include "Core/Input.h"
#include <SDL.h>
#include <unordered_map>
#include <PlayerController.h>
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

	static bool GetKeyDown(SDL_Scancode);
	static bool GetKeyUp(SDL_Scancode);
	static bool GetKey(SDL_Scancode);

	static Input* Init();
	void Listen(float deltaTime);
	void Reset();

	inline void AddCallback(const EventCallbackFunc& callback, EventType type) {
		if (callbacks.count(type) == 0) {
			callbacks[type].emplace_back(callback);
		}
	}

	template <typename T, typename = std::enable_if_t<std::is_base_of<Event, T>::value>>
	inline void FireEvent(Event& event) {
		std::unordered_map<EventType, std::vector<CallbackData>>::iterator it;
		for (it = callbacks.begin(); it != callbacks.end(); it++) {
			if (event.GetEventType() == it->first) {
				EventDispatcher dispatcher(event);
				for (int i = 0; i < it->second.size(); i++) {
					dispatcher.Dispatch<T>(it->second[i].EventCallback);
				}
			}
		}
	}

	/// <summary>
	/// Warning: Same function can be added several times.
	/// </summary>
	static inline void AddInputCallback(const EventCallbackFunc& callback, SDL_Scancode keyCode) {
		instance->inputCallbacks[keyCode].emplace_back(callback);
	}

	/// <summary>
	/// Nothing happens if you try to remove the same method twice.
	/// </summary>
	static inline void RemoveInputCallback(const EventCallbackFunc& callback, SDL_Scancode keyCode) {
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

	CallbackData GenericCallback;

	std::unordered_map<EventType, std::vector<CallbackData>> callbacks;


	void FireEvent(Event& event, CallbackData data);
	//EventDispatcher dispatcher;

};