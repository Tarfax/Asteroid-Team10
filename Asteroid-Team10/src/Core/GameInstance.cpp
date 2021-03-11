#include "GameInstance.h"
#include "Component/Asteroid.h"
#include "Component/ParticleSystem.h"
#include "SoundSystem/SoundCoordinator.h"
#include <FSM/MainMenuState.h>
#include <FSM/HighScoreState.h>

//#define BindFunction(x, y) std::bind(&x, y, std::placeholders::_1)

//const int SCREEN_WIDTH {640};
//const int SCREEN_HEIGHT {480};

GameInstance::GameInstance() {
	//Asteroid::AddCallback(BindFunction(GameInstance::OnEvent, this));
}

void GameInstance::Init() {
	ChangeToState<MainMenuState>();

	//CreateMainMenu();
	//CreateLevel();
}

//
//void GameInstance::CreateMainMenu() {
//	mainMenu = new MainMenuState();
//	mainMenu->OnEnter();
//	mainMenu->AddCallback(BindFunction(GameInstance::OnEvent, this));
//}


void GameInstance::Update(float deltaTime) {
	//if (callFunctionNextFrame == true) {
	//	timer -= deltaTime;
	//}

	//if (callFunctionNextFrame == true && timer <= 0) {
	//	callback(nullptr);
	//	
	//}

	if (switchToNewState == true) {
		SwitchState();
		switchToNewState = false;
	}

	state->Update(deltaTime);
	//if (mainMenu == nullptr && timer <= 0) {
	//	CreateMainMenu();
	//	timer = 0.25f;
	//}
}

void GameInstance::Destroy() {
	state->Exit();
	delete state;
	state = nullptr;
}

void GameInstance::SwitchState() {
	if (state != nullptr) {
		std::cout << "Update::state " << state->ToString() << std::endl;
		std::cout << "Update::newState " << newState->ToString() << std::endl;

		state->Exit();
	}
	delete state;
	state = newState;
	state->Enter(this);
	newState = nullptr;
}

//
//void GameInstance::CreateLevel(int level) {
//	int height = SCREEN_HEIGHT / 3;
//
//	for (int i = 0; i < level + 4; i++) {
//		GameObject* gameObject = Factory::GetInstance<Asteroid>(Predef::Asteroid_Lvl1);
//		Transform* transform = gameObject->GetComponent<Transform>();
//		if (i % 2 == 0) {
//			transform->Position() = Vector2(32, height * (i + 1));
//		}
//		else {
//			transform->Position() = Vector2(SCREEN_WIDTH - 32, height * (i + 1));
//		}
//
//		asteroidsInPlay++;
//	}
//
//}

//
//bool GameInstance::OnAsteroidDestroyed(AsteroidDestroyedEvent& e) {
//	asteroidsInPlay--;
//	BoxCollider2D* collider = e.gameObject->GetComponent<BoxCollider2D>();
//
//	if (e.Level == 1) {
//		for (int i = 0; i < 2; i++) {
//			GameObject* gameObject = Factory::GetInstance<Asteroid>(Predef::Asteroid_Lvl2);
//			Transform* transform = gameObject->GetComponent<Transform>();
//			transform->Position() = collider->GetOrigin();
//			asteroidsInPlay++;
//
//		}
//	}
//	else if (e.Level == 2) {
//		BoxCollider2D* collider = e.gameObject->GetComponent<BoxCollider2D>();
//		for (int i = 0; i < 2; i++) {
//			GameObject* gameObject = Factory::GetInstance<Asteroid>(Predef::Asteroid_Lvl3);
//			Transform* transform = gameObject->GetComponent<Transform>();
//			transform->Position() = collider->GetOrigin();
//			asteroidsInPlay++;
//		}
//	}
//
//	//std::cout << "Asteroids left " << asteroidsInPlay << std::endl;
//	if (asteroidsInPlay == 0) {
//		std::cout << "YOU OWN!!! CHOO CHOO!!" << std::endl;
//		//CreateLevel(currentLevel++);
//	}
//
//	GameObject* gameObject = Factory::GetInstance<ParticleSystem>(Predef::AsteroidExplosion);
//	gameObject->GetComponent<Transform>()->Position() = collider->GetOrigin();
//	SoundCoordinator::PlayEffect("Assets/SoundFx/explosion.wav");
//	return false;
//}

/* ---  EVENTS --- */

//void GameInstance::OnEvent(Event& e) {
//	EventDispatcher dispatcher(e);
//	dispatcher.Dispatch<AsteroidDestroyedEvent>(BindFunction(GameInstance::OnAsteroidDestroyed, this));
//	dispatcher.Dispatch<MenuQuitGameEvent>(BindFunction(GameInstance::OnMenuQuitGameEvent, this));
//	dispatcher.Dispatch<MenuStartGameEvent>(BindFunction(GameInstance::OnMenuStartGameEvent, this));
//}
//
//bool GameInstance::OnMenuQuitGameEvent(MenuQuitGameEvent& e) {
//	//callback = BindFunction(GameInstance::QuitGame, this);
//	//callFunctionNextFrame = true;
//	return true;
//}

//void GameInstance::QuitGame(void*) {
//	DestroyMainMenu();
//}
//
//bool GameInstance::OnMenuStartGameEvent(MenuStartGameEvent& e) {
//	callback = BindFunction(GameInstance::StartGame, this);
//	callFunctionNextFrame = true;
//	timer = 0.5;
//	std::cout << "start game event\n";
//	return true;
//}
//
//void GameInstance::StartGame(void*) {
//	DestroyMainMenu();
//	callback = BindFunction(GameInstance::CreatePlayer, this);
//	callFunctionNextFrame = true;
//	timer = 0.25;
//	std::cout << "delete main menu\n";
//
//}

//void GameInstance::CreatePlayer(void*) {
//	GameObject* gameObject = Factory::GetInstance<PlayerController>(Predef::Player);
//	playerTransform = gameObject->GetComponent<Transform>();
//	playerTransform->Position() = Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
//	callback = BindFunction(GameInstance::CreateFirstLevel, this);
//	callFunctionNextFrame = true;
//	timer = 2;
//	std::cout << "create player\n";
//
//}
//
//void GameInstance::CreateFirstLevel(void*) {
//	std::cout << "create level\n";
//
//	CreateLevel(currentLevel++);
//	callback = nullptr;
//	callFunctionNextFrame = false;
//}

//void GameInstance::DestroyMainMenu() {
//	mainMenu->OnExit();
//	delete mainMenu;
//	mainMenu = nullptr;
//}