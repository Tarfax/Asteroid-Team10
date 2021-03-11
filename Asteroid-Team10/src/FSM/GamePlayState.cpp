#include "GamePlayState.h"
#include "Core/Engine.h"
#include "FactorySystem/Factory.h"
#include "SoundSystem/SoundCoordinator.h"
#include "PlayerController.h"
#include <string>

void GamePlayState::OnEnter() {
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

	for (int i = 0; i < 3; i++) 	{
		lifeImages[i]->SetPosition(lifeImagesPosition + Vector2(22 * i, 0));
		lifeImages[i]->SetRotation(-90);
		lifeImages[i]->SetScale(0.85f);
	}

	canvas->AddUIElement(life1);
	canvas->AddUIElement(life2);
	canvas->AddUIElement(life3);

	CreatePlayer();
	CreateLevel(currentLevel++);
	//ADD UI LAYOUT
}

void GamePlayState::OnUpdate(float deltaTime) {

}

void GamePlayState::OnExit() {
	GameObject::Destroy(playerTransform->gameObject);
	GameObject::Destroy(canvas->gameObject);
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
		
		SetScore(20);
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
		SetScore(100);
	}
	else {
		//Add score
		SetScore(100);
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

void GamePlayState::SetScore(int score) {
	this->score += score;
	canvas->RemoveUIElement(scoreText);
	scoreText->Destroy();
	delete scoreText;
	scoreText = UIFactory::CreateText(std::to_string(this->score), {255, 255, 255, 255}, 50);
	scoreText->SetPosition(scoreTextPosition);
	canvas->AddUIElement(scoreText);
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
