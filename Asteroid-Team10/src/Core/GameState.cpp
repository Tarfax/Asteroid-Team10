#include "GameState.h"
#include "Component/Asteroid.h"
#include "Component/ParticleSystem.h"
#include "SoundSystem/SoundCoordinator.h"

#define CreateFunctionCallback(x, y) std::bind(&x, y, std::placeholders::_1)

const int SCREEN_WIDTH {640};
const int SCREEN_HEIGHT {480};

GameState::GameState() {
	Asteroid::AddCallback(CreateFunctionCallback(GameState::OnEvent, this));
	GameObject* gameObject = Factory::GetInstance<PlayerController>(Predef::Player);
	playerTransform = gameObject->GetComponent<Transform>();
}

void GameState::Init() {
	Level01();
	playerTransform->Position() = Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void GameState::OnEvent(Event& e) {
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<AsteroidDestroyedEvent>(CreateFunctionCallback(GameState::OnAsteroidDestroyed, this));
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

	std::cout << "Asteroids left " << asteroidsInPlay << std::endl;
	if (asteroidsInPlay == 0) {
		std::cout << "YOU OWN!!! CHOO CHOO!!" << std::endl;
	}

	GameObject* gameObject = Factory::GetInstance<ParticleSystem>(Predef::AsteroidExplosion);
	gameObject->GetComponent<Transform>()->Position() = collider->GetOrigin();
	SoundCoordinator::PlayEffect("Assets/SoundFx/explosion.wav");
	return false;
}