#include "GamePlayState.h"
#include "MainMenuState.h"
#include "Core/Engine.h"
//#include "FactorySystem/Factory.h"
//#include "SoundSystem/SoundCoordinator.h"
#include "PlayerController.h"
#include <EventSystem/MenuEvent.h>
#include <string>

void GamePlayState::OnEnter() {
	Input::AddInputCallback(BindFunction(GamePlayState::OnEvent, this), SDL_SCANCODE_ESCAPE);

	Asteroid::AddCallback(BindFunction(GamePlayState::OnEvent, this));

	GameObject* canvasGO = new GameObject();
	canvas = canvasGO->AddComponent<Canvas>();

	scoreText = UIFactory::CreateText("00", {255, 255, 255, 255}, 50);
	scoreText->SetPosition(scoreTextPosition);

	canvas->AddUIElement(scoreText);

	Image* life1 = new Image("Assets/Sprites/ship.png");
	Image* life2 = new Image("Assets/Sprites/ship.png");
	Image* life3 = new Image("Assets/Sprites/ship.png");

	life1->Init();
	life2->Init();
	life3->Init();

	lifeImages.push_back(life1);
	lifeImages.push_back(life2);
	lifeImages.push_back(life3);

	for (int i = 0; i < 3; i++) {
		lifeImages[i]->SetPosition(lifeImagesPosition + Vector2(22 * i, 0));
		lifeImages[i]->SetRotation(-90);
		lifeImages[i]->SetScale(0.85f);
	}

	canvas->AddUIElement(life1);
	canvas->AddUIElement(life2);
	canvas->AddUIElement(life3);

	CreatePlayer();
	loadNextLevel = true;
	timer = timeToLoadLevel;


	isPaused = false;
	gameInstance->SetPaused(isPaused);
	gameInstance->SetTimeScale(isPaused ? 0 : 1);
}

void GamePlayState::OnUpdate(float deltaTime) {
	if (loadNextLevel == true && isPaused == false) {
		timer -= deltaTime;
		if (timer < 0.0f) {
			CreateLevel(currentLevel++);
			loadNextLevel = false;
			timer = timeToLoadLevel;
			SoundCoordinator::PlayEffect("Assets/SoundFx/levelBegin.wav");
		}
	}
}

void GamePlayState::OnExit() {
	GameObject::Destroy(playerTransform->gameObject, Predef::Player);
	GameObject::Destroy(canvas->gameObject, Predef::Unknown);

	std::map<int, GameObject*>::iterator it;
	for (it = spawnedObjects.begin(); it != spawnedObjects.end(); it++) 	{
		/*GameObject::Destroy(it->second, Predef::);*/
		std::cout << "GamePlayState::OnExit() must destroy all objects, but how?" << std::endl;
	}
	spawnedObjects.clear();

	Input::RemoveInputCallback(BindFunction(GamePlayState::OnEvent, this), SDL_SCANCODE_ESCAPE);
	Asteroid::RemoveCallback(BindFunction(GamePlayState::OnEvent, this));
	if (pauseMenu != nullptr) {
		pauseMenu->Destroy();
		delete pauseMenu;
		pauseMenu = nullptr;
	}
}

void GamePlayState::CreatePlayer() {
	GameObject* gameObject = Factory::Create<PlayerController>(Predef::Player);
	playerTransform = gameObject->GetComponent<Transform>();
	playerTransform->Position() = Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

}

void GamePlayState::CreateLevel(int level) {

	int height = SCREEN_HEIGHT / 3;

	for (int i = 0; i < level + 4; i++) {
		GameObject* gameObject = Factory::Create<Asteroid>(Predef::Asteroid_Lvl1);
		Transform* transform = gameObject->GetComponent<Transform>();
		if (i % 2 == 0) {
			transform->Position() = Vector2(32, height * (i + 1));
		}
		else {
			transform->Position() = Vector2(SCREEN_WIDTH - 32, height * (i + 1));
		}

		asteroidsInPlay++;
		spawnedObjects[gameObject->id] = gameObject;
		//gameObject->SetActive(true);

	}

}

//void GamePlayState::CreateLevel(int level) {
//
//	int height = SCREEN_HEIGHT / 3;
//
//	for (int i = 0; i < level + 4; i++) {
//		//GameObject* gameObject = Factory::Create<Asteroid>(Predef::Asteroid_Lvl1);
//		GameObject* gameObject = ObjectPool::FetchObject(AsteroidLvl1Pool);
//		Transform* transform = gameObject->GetComponent<Transform>();
//		if (i % 2 == 0) {
//			transform->Position() = Vector2(32, height * (i + 1));
//		}
//		else {
//			transform->Position() = Vector2(SCREEN_WIDTH - 32, height * (i + 1));
//		}
//		asteroidsInPlay++;
//	}
//
//}
//

void GamePlayState::SetScore(int score) {
	this->score += score;
	canvas->RemoveUIElement(scoreText);
	scoreText->Destroy();
	delete scoreText;
	scoreText = UIFactory::CreateText(std::to_string(this->score), {255, 255, 255, 255}, 50);
	scoreText->SetPosition(scoreTextPosition);
	canvas->AddUIElement(scoreText);
}



void GamePlayState::OnEvent(Event& e) {
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<AsteroidDestroyedEvent>(BindFunction(GamePlayState::OnAsteroidDestroyed, this));
	dispatcher.Dispatch<KeyPressedEvent>(BindFunction(GamePlayState::OnKeyPressed, this));

	dispatcher.Dispatch<MenuResumeGameEvent>(BindFunction(GamePlayState::OnResumeGame, this));
	dispatcher.Dispatch<MenuMainMenuEvent>(BindFunction(GamePlayState::OnMainMenu, this));
}


bool GamePlayState::OnKeyPressed(KeyPressedEvent& e) {
	if (e.GetKeyCode() == SDL_SCANCODE_ESCAPE && e.GetRepeatCount() == 0) {
		isPaused = !isPaused;
		gameInstance->SetPaused(isPaused);
		gameInstance->SetTimeScale(isPaused ? 0 : 1);
		if (isPaused == true) {
			pauseMenu = new PauseMenu();
			pauseMenu->Init();
			pauseMenu->AddCallback(BindFunction(GamePlayState::OnEvent, this));
		}
		else {
			pauseMenu->Destroy();
			delete pauseMenu;
			pauseMenu = nullptr;
		}
	}
	return true;
	//gameObject->SetActive(true);
}

bool GamePlayState::OnAsteroidDestroyed(AsteroidDestroyedEvent& e) {
	std::cout << "GamePlayState::OnAsteroidDestroyed" << std::endl;
	spawnedObjects.erase(e.gameObject->id);
	asteroidsInPlay--;

	BoxCollider2D* collider = e.gameObject->GetComponent<BoxCollider2D>();

	if (e.Level == 1) {
		for (int i = 0; i < 2; i++) {
			GameObject* gameObject = Factory::Create<Asteroid>(Predef::Asteroid_Lvl2);
			//GameObject* gameObject = ObjectPool::FetchObject(AsteroidLvl2Pool);
			Transform* transform = gameObject->GetComponent<Transform>();
			transform->Position() = collider->GetOrigin();
			asteroidsInPlay++;
			gameObject->SetActive(true);
			spawnedObjects[gameObject->id] = gameObject;
		}

		//Add score

		SetScore(20);
	}
	else if (e.Level == 2) {
		BoxCollider2D* collider = e.gameObject->GetComponent<BoxCollider2D>();
		for (int i = 0; i < 2; i++) {
			GameObject* gameObject = Factory::Create<Asteroid>(Predef::Asteroid_Lvl3);
			//GameObject* gameObject = ObjectPool::FetchObject(AsteroidLvl3Pool);
			Transform* transform = gameObject->GetComponent<Transform>();
			transform->Position() = collider->GetOrigin();
			asteroidsInPlay++;
			spawnedObjects[gameObject->id] = gameObject;
			gameObject->SetActive(true);
		}

		//Add score
		SetScore(100);
	}
	else {
		//Add score
		SetScore(100);
	}

	

	//std::cout << "Asteroids left " << asteroidsInPlay << std::endl;
	if (asteroidsInPlay == 0) {
		std::cout << "YOU OWN!!! CHOO CHOO!!" << std::endl;
		loadNextLevel = true;
	}

	GameObject* gameObject = Factory::Create<ParticleSystem>(Predef::AsteroidExplosion);
	gameObject->GetComponent<Transform>()->Position() = collider->GetOrigin();
	SoundCoordinator::PlayEffect("Assets/SoundFx/explosion.wav");
	gameObject->SetActive(true);
	return false;
}

bool GamePlayState::OnResumeGame(MenuResumeGameEvent& e) {
	isPaused = !isPaused;
	gameInstance->SetPaused(isPaused);
	gameInstance->SetTimeScale(isPaused ? 0 : 1);
	pauseMenu->Destroy();
	delete pauseMenu;
	pauseMenu = nullptr;
	SoundCoordinator::PlayEffect("Assets/SoundFx/menuEnter2.wav");
	return true;
}

bool GamePlayState::OnMainMenu(MenuMainMenuEvent& e) {
	SoundCoordinator::PlayEffect("Assets/SoundFx/menuEnter2.wav");
	gameInstance->ChangeToState<MainMenuState>();
	return true;
}

