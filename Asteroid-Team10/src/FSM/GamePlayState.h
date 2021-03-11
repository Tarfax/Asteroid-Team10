#pragma once
#include <FSM/GameState.h>
#include "Component/Asteroid.h"
#include "EventSystem/ObjectEvent.h"
#include "FSM/PauseMenu.h"

class GamePlayState: public GameState {
public:
	void OnEnter() override;
	void OnUpdate(float deltaTime) override;
	void OnExit() override;

private:
	void OnEvent(Event& e);
	bool OnAsteroidDestroyed(AsteroidDestroyedEvent& e);
	bool OnKeyPressed(KeyPressedEvent& e);

	void SetScore(int score);

	void CreateLevel(int level);
	void CreatePlayer();

	bool OnResumeGame(MenuResumeGameEvent& e);
	bool OnMainMenu(MenuMainMenuEvent& e);

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

	float timer;
	float timeToLoadLevel = 3.0f;
	bool loadNextLevel = false;

	bool isPaused = false;

	PauseMenu* pauseMenu;

	std::map<int, GameObject*> spawnedObjects;
};