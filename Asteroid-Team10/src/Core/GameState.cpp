#include "GameState.h"
#include "Component/Asteroid.h"
#include "Component/ParticleSystem.h"
#include "SoundSystem/SoundCoordinator.h"

#define BindFunction(x, y) std::bind(&x, y, std::placeholders::_1)

const int SCREEN_WIDTH {640};
const int SCREEN_HEIGHT {480};

GameState::GameState() {
	Asteroid::AddCallback(BindFunction(GameState::OnEvent, this));
}

void GameState::Init() {
	timer = time;
	CreateMainMenu();

	//Level01();
	
}

void GameState::CreateMainMenu() {
	mainMenu = new MainMenu();
	mainMenu->Init();
	mainMenu->AddCallback(BindFunction(GameState::OnEvent, this));
}


void GameState::Update(float deltaTime) {
	if (callFunctionNextFrame == true) {
		callback(nullptr);
		callback = nullptr;
		callFunctionNextFrame = false;
	}

	//if (mainMenu == nullptr) {
	//	timer -= deltaTime;
	//}

	//if (mainMenu == nullptr && timer <= 0) {
	//	CreateMainMenu();
	//	timer = 0.25f;
	//}
}


void GameState::Level01() {
	int height = SCREEN_HEIGHT / 3;

	for (int i = 0; i < 4; i++) {
		GameObject* gameObject = Factory::GetInstance<Asteroid>(Predef::Asteroid_Lvl1);
		Transform* transform = gameObject->GetComponent<Transform>();
		if (i % 2 == 0) {
			transform->Position() = Vector2(32, height * (i + 1));
		}
		else {
			transform->Position() = Vector2(SCREEN_WIDTH - 32, height * (i + 1));
		}

		asteroidsInPlay++;
	}

}




bool GameState::OnAsteroidDestroyed(AsteroidDestroyedEvent& e) {
	asteroidsInPlay--;
	BoxCollider2D* collider = e.gameObject->GetComponent<BoxCollider2D>();

	if (e.Level == 1) {
		for (int i = 0; i < 2; i++) {
			GameObject* gameObject = Factory::GetInstance<Asteroid>(Predef::Asteroid_Lvl2);
			Transform* transform = gameObject->GetComponent<Transform>();
			transform->Position() = collider->GetOrigin();
			asteroidsInPlay++;

		}
	}
	else if (e.Level == 2) {
		BoxCollider2D* collider = e.gameObject->GetComponent<BoxCollider2D>();
		for (int i = 0; i < 2; i++) {
			GameObject* gameObject = Factory::GetInstance<Asteroid>(Predef::Asteroid_Lvl3);
			Transform* transform = gameObject->GetComponent<Transform>();
			transform->Position() = collider->GetOrigin();
			asteroidsInPlay++;
		}
	}

	//std::cout << "Asteroids left " << asteroidsInPlay << std::endl;
	if (asteroidsInPlay == 0) {
		std::cout << "YOU OWN!!! CHOO CHOO!!" << std::endl;
	}

	GameObject* gameObject = Factory::GetInstance<ParticleSystem>(Predef::AsteroidExplosion);
	gameObject->GetComponent<Transform>()->Position() = collider->GetOrigin();
	SoundCoordinator::PlayEffect("Assets/SoundFx/explosion.wav");
	return false;
}

/* ---  EVENTS --- */

void GameState::OnEvent(Event& e) {
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<AsteroidDestroyedEvent>(BindFunction(GameState::OnAsteroidDestroyed, this));
	dispatcher.Dispatch<MenuQuitGameEvent>(BindFunction(GameState::OnMenuQuitGameEvent, this));
	dispatcher.Dispatch<MenuStartGameEvent>(BindFunction(GameState::OnMenuStartGameEvent, this));
}

bool GameState::OnMenuQuitGameEvent(MenuQuitGameEvent& e) {
	callback = BindFunction(GameState::QuitGame, this);
	callFunctionNextFrame = true;
	return true;
}

bool GameState::OnMenuStartGameEvent(MenuStartGameEvent& e) {
	callback = BindFunction(GameState::StartGame, this);
	callFunctionNextFrame = true;
	return true;
}

void GameState::QuitGame(void*) {
	DestroyMainMenu();
}

void GameState::StartGame(void*) {
	DestroyMainMenu();
	GameObject* gameObject = Factory::GetInstance<PlayerController>(Predef::Player);
	playerTransform = gameObject->GetComponent<Transform>();
	playerTransform->Position() = Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	Level01();
}

void GameState::DestroyMainMenu() {
	mainMenu->Destroy();
	delete mainMenu;
	mainMenu = nullptr;
}


