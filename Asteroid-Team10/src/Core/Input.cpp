#include "Core/Input.h"
#include <string>
#include <Core/Engine.h>

Input* Input::instance = nullptr;

Input* Input::Init() {
	instance = (instance != nullptr) ? instance : new Input();
	instance->keyStates = SDL_GetKeyboardState(nullptr);
	return instance;
}

void Input::Listen(float deltaTime) {
	this->deltaTime = deltaTime;

	while (SDL_PollEvent(&e) == true) {
		// switch to allow further implementation of inputs.
		switch (e.type) {

			case SDL_KEYDOWN:
				KeyDown();
				break;
			case SDL_KEYUP:
				KeyUp();
				break;
			case SDL_QUIT:
				//hasQuitBeenCalled = true;

				EngineCloseEvent event { };
				FireEvent(event, GenericCallback);
				break;
		}

	}

}


void Input::Reset() {
	std::unordered_map<SDL_Scancode, bool>::iterator it;
	for (it = wasKeyUp.begin(); it != wasKeyUp.end(); it++) {
		wasKeyUp[it->first] = false;
	}
}

void Input::FireEvent(Event& event, CallbackData data) {
	data.EventCallback(event);
	//CallbackData& data = /**(CallbackData*)*//*Engine::GetEmptyPointer()*/ /*&*/this->data;

	//KeyPressedEvent event {1,2 };
	//data.EventCallback = this->data.EventCallback;
	//data.keyStates = 
	//std::cout << data.info << std::endl;

	//data.EventCallback(event);
}

bool Input::GetKeyDown(SDL_Scancode key) {
	if (instance->keyStates[key] == 1) {
		if (instance->keyStateFrameCount[key] > 0) {
			instance->keyStateFrameCount[key]++;
			return false;
		}
		//std::cout << key << " was pressed" << std::endl;
		instance->keyStateFrameCount[key]++;
		return true;
	}
	return false;
}

bool Input::GetKeyUp(SDL_Scancode key) {
	if (instance->wasKeyUp.count(key) == 1) {
		return instance->wasKeyUp[key] == true;
	}
	else {
		instance->wasKeyUp[key] = true;
		return true;
	}
	return false;
}

bool Input::GetKey(SDL_Scancode key) {
	return instance->keyStateFrameCount[key] > 1;
}


void Input::KeyDown() {
	keyStates = SDL_GetKeyboardState(nullptr);
	std::cout << "Input::KeyDown()" << "\n ";

	std::unordered_map<SDL_Scancode, std::vector<CallbackData>>::iterator it;
	for (it = inputCallbacks.begin(); it != inputCallbacks.end(); it++) {
		SDL_Scancode key = it->first;
		std::cout << "checking key " << key << "\n ";
		if (keyStates[key] == 1) {
			if (keyStateFrameCount.count(key) != 1) {
				keyStateFrameCount[key] = 0;
			}

			std::cout << "key " << key << " was found\n ";

			KeyPressedEvent event {key, instance->keyStateFrameCount[key], deltaTime};

			for (int i = 0; i < it->second.size(); i++) {
				FireEvent(event, it->second[i]);
			}

			keyStateFrameCount[key]++;
		}
	}

	//for (int i = 0; i < inputCallbacks.size(); i++) {
	//	SDL_Scancode key = inputCallbacks[i].key;
	//	if (keyStates[key] == 1) {
	//		if (keyStateFrameCount.count(key) != 1) {
	//			keyStateFrameCount[key] = 0;
	//		}
	//		KeyPressedEvent event {key, instance->keyStateFrameCount[key]};
	//		FireEvent(event, inputCallbacks[i]);
	//		keyStateFrameCount[key]++;
	//	}
	//}
}

void Input::KeyUp() {
	keyStates = SDL_GetKeyboardState(nullptr);

	std::unordered_map<SDL_Scancode, int>::iterator it;
	for (it = keyStateFrameCount.begin(); it != keyStateFrameCount.end(); it++) {
		if (keyStates[it->first] == 0 && it->second > 0) {


			KeyReleasedEvent event {it->first};

			for (int i = 0; i < inputCallbacks[it->first].size(); i++) {
				FireEvent(event, inputCallbacks[it->first][i]);
			}
			//FireEvent(event, );
			//instance->data.EventCallback(event);
			//std::cout << it->first << " was released" << std::endl;
			wasKeyUp[it->first] = true;
			it->second = 0;
		}
	}

}
