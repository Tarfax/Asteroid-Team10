#include "GamePlayState.h"
#include "Core/Engine.h"
#include "FactorySystem/Factory.h"
#include "SoundSystem/SoundCoordinator.h"
#include "PlayerController.h"

void GamePlayState::OnEnter() {
	Asteroid::AddCallback(BindFunction(GamePlayState::OnEvent, this));

	CreatePlayer();
	CreateLevel(currentLevel++);
	//ADD UI LAYOUT
}

void GamePlayState::OnUpdate(float deltaTime) {

}

void GamePlayState::OnExit() {
	GameObject::Destroy(playerTransform->gameObject);
}

void GamePlayState::OnEvent(Event& e) {
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<AsteroidDestroyedEvent>(BindFunction(GamePlayState::OnAsteroidDestroyed, this));
}

void GamePlayState::CreatePlayer() {
	GameObject* gameObject = Factory::GetInstance<PlayerController>(Predef::Player);
	playerTransform = gameObject->GetComponent<Transform>();
	playerTransform->Position() = Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

}

bool GamePlayState::OnAsteroidDestroyed(AsteroidDestroyedEvent& e) {
	asteroidsInPlay--;
	BoxCollider2D* collider = e.gameObject->GetComponent<BoxCollider2D>();

	if (e.Level == 1) {
		for (int i = 0; i < 2; i++) {
			GameObject* gameObject = Factory::GetInstance<Asteroid>(Predef::Asteroid_Lvl2);
			Transform* transform = gameObject->GetComponent<Transform>();
			transform->Position() = collider->GetOrigin();
			asteroidsInPlay++;

		}

		//Add score

	}
	else if (e.Level == 2) {
		BoxCollider2D* collider = e.gameObject->GetComponent<BoxCollider2D>();
		for (int i = 0; i < 2; i++) {
			GameObject* gameObject = Factory::GetInstance<Asteroid>(Predef::Asteroid_Lvl3);
			Transform* transform = gameObject->GetComponent<Transform>();
			transform->Position() = collider->GetOrigin();
			asteroidsInPlay++;
		}
		
		//Add score

	}
	else {
		
		//Add score
	}

	//std::cout << "Asteroids left " << asteroidsInPlay << std::endl;
	if (asteroidsInPlay == 0) {
		std::cout << "YOU OWN!!! CHOO CHOO!!" << std::endl;
		CreateLevel(currentLevel++);
	}

	GameObject* gameObject = Factory::GetInstance<ParticleSystem>(Predef::AsteroidExplosion);
	gameObject->GetComponent<Transform>()->Position() = collider->GetOrigin();
	SoundCoordinator::PlayEffect("Assets/SoundFx/explosion.wav");
	return false;
}

void GamePlayState::CreateLevel(int level) {

	int height = SCREEN_HEIGHT / 3;

	for (int i = 0; i < level + 4; i++) {
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
