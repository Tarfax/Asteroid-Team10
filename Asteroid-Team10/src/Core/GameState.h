#pragma once

#include <EventSystem/ObjectEvent.h>
#include "PlayerController.h"


class GameState {
public: 
	GameState();
	void Init();
private: 
	void OnEvent(Event& e);
	bool OnAsteroidDestroyed(AsteroidDestroyedEvent& e);

	void Level01();

	Transform* playerTransform;

	int asteroidsInPlay = 0;
};