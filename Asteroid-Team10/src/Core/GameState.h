#pragma once

#include <EventSystem/ObjectEvent.h>


class GameState {
public: 
	GameState();

private: 
	void OnEvent(Event& e);
	bool OnObjectDestroyed(ObjectDestroyedEvent& e);
};