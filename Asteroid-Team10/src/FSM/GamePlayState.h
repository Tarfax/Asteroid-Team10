#pragma once
#include <FSM/GameState.h>
#include "Component/Asteroid.h"
#include "EventSystem/ObjectEvent.h"

class GamePlayState: public GameState {
public:
	void OnEnter() override;
	void OnUpdate(float deltaTime) override;
	void OnExit() override;

private:
	void OnEvent(Event& e);
	bool OnAsteroidDestroyed(AsteroidDestroyedEvent& e);

	void SetScore(int score);

	void CreateLevel(int level);
	void CreatePlayer();

	int asteroidsInPlay = 0;
	int currentLevel;

	Transform* playerTransform;

	Vector2 scoreTextPosition = {25, 10};
	Text* scoreText;
	int score;

	int life;
	Vector2 lifeImagesPosition = {20, 50};
	std::vector<Image*> lifeImages;

	Canvas* canvas;

};