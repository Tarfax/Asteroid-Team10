#include "PlayerController.h"
#include "Core/Input.h"
#include <SDL.h>
#include <Math/Mathf.h>
#include <Component/PositionWrapper.h>
#include <Component/Projectile.h>
#include <Component/Core/BoxCollider2D.h>
#include <Component/Core/SpriteRenderer.h>
#include "Structs/Sprite.h"
#include "FactorySystem/Factory.h"
#include "FactorySystem/ObjectDefinitions.h"
#include "SoundSystem/SoundCoordinator.h"

PlayerController* PlayerController::playerController = nullptr;

void PlayerController::Init() {
	playerController = this;

	targetSpeed = speed;

	transform = gameObject->GetComponent<Transform>();

	SpriteRenderer* renderer = gameObject->AddComponent<SpriteRenderer>();
	PositionWrapper* positionWrapper = gameObject->AddComponent<PositionWrapper>();

	Input::AddInputCallback(BindFunction(PlayerController::OnEvent, this), SDL_SCANCODE_W);
	Input::AddInputCallback(BindFunction(PlayerController::OnEvent, this), SDL_SCANCODE_A);
	Input::AddInputCallback(BindFunction(PlayerController::OnEvent, this), SDL_SCANCODE_S);
	Input::AddInputCallback(BindFunction(PlayerController::OnEvent, this), SDL_SCANCODE_D);
	Input::AddInputCallback(BindFunction(PlayerController::OnEvent, this), SDL_SCANCODE_SPACE);
}


void PlayerController::OnSetData(ObjectData* data) {
	PlayerData* playerData = dynamic_cast<PlayerData*>(data);
	speed = playerData->Speed;
	rotationSpeed = playerData->RotationSpeed;
	acceleration = playerData->Acceleration;
	fireRate = playerData->FireRate;
	momentumAcceleration = playerData->MomentumAcceleration;

	SpriteRenderer* renderer = gameObject->GetComponent<SpriteRenderer>();
	renderer->SetSprite(Sprite::CreateSprite(data->TextureIds[0]));

	PositionWrapper* positionWrapper = gameObject->GetComponent<PositionWrapper>();
	positionWrapper->SetTexDimensions(renderer->GetRect());

	BoxCollider2D* collider = gameObject->GetComponent<BoxCollider2D>();
	collider->SetBounds(renderer->GetRect());
	collider->SetLayer(Layer::lPlayer);
	collider->SetCollideWithLayer(Layer::lNothing);
}

void PlayerController::OnEvent(Event& e) {
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<KeyPressedEvent>(BindFunction(PlayerController::OnKeyPressedEvent, this));
}

bool PlayerController::OnKeyPressedEvent(KeyPressedEvent& e) {
	if (e.GetKeyCode() == SDL_SCANCODE_W) {
		targetSpeed = speed;

		momentum.X = IncrementTowards(momentum.X, transform->forward.X, momentumAcceleration, e.GetDeltaTime());
		momentum.Y = IncrementTowards(momentum.Y, transform->forward.Y, momentumAcceleration, e.GetDeltaTime());

		//momentum.X = transform->forward.X;
		//momentum.Y = transform->forward.Y;
		//currentSpeed = IncrementTowards(currentSpeed, targetSpeed, acceleration, e.GetDeltaTime());
		float time = 0.04f;
		static float timer;
		timer -= e.GetDeltaTime();
		if (timer <= 0) {
			SoundCoordinator::PlayEffect("Assets/SoundFx/engine.wav");
			timer = time;
		}
	}

	if (e.GetKeyCode() == SDL_SCANCODE_A) {
		transform->Rotation() -= (double)(rotationSpeed * e.GetDeltaTime());
	}

	if (e.GetKeyCode() == SDL_SCANCODE_D) {
		transform->Rotation() += (double)(rotationSpeed * e.GetDeltaTime());
	}

	if (e.GetKeyCode() == SDL_SCANCODE_SPACE) {
		if (fireRateTimer <= 0.0f) {
			if (e.GetDeltaTime() != 0) {
				Fire();
				fireRateTimer = fireRate;
			}
		}
	}

	return true;
}

void PlayerController::Update(float deltaTime) {

	currentSpeed = IncrementTowards(currentSpeed, targetSpeed, acceleration, deltaTime);
	targetSpeed = currentSpeed * 0.99995f;
	//momentum.X *= 0.9999f;
	//momentum.Y *= 0.9999f;

	fireRateTimer -= deltaTime;

	HandleInput(deltaTime);


	transform->Translate(Vector2((currentSpeed * deltaTime) * momentum.X, (currentSpeed * deltaTime) * momentum.Y));
}


void PlayerController::HandleInput(float deltaTime) {
	if (Input::GetKeyDown(SDL_SCANCODE_H)) {
		transform->Scale().X -= 1 * deltaTime;
	}
}


void PlayerController::Fire() {
	GameObject* gameObject = Factory::Create<Projectile>(Predef::Projectile);
	//GameObject* gameObject = objectPool->FetchObject(ProjectilePool);

	Transform* projectileTransform = gameObject->GetComponent<Transform>();

	Vector2 position = this->transform->Position();
	float rotation = this->transform->Rotation();

	float x = cos(Mathf::DegToRad(rotation));
	float y = sin(Mathf::DegToRad(rotation));

	int width = this->gameObject->GetComponent<BoxCollider2D>()->GetBounds().w;
	int height = this->gameObject->GetComponent<BoxCollider2D>()->GetBounds().h;

	position.X += (width / 2 * x) + width / 2;
	position.Y += (height / 2 * y) + height / 2;

	projectileTransform->Position() = position;
	gameObject->GetComponent<BoxCollider2D>()->ResetBounds();
	Projectile* projectile = gameObject->GetComponent<Projectile>();
	projectile->SetDirection(this->transform->forward);

	SoundCoordinator::PlayEffect("Assets/SoundFx/fire4.wav");

	gameObject->SetActive(true);
}


float PlayerController::IncrementTowards(float n, float target, float alpha, float deltaTime) {
	if (n == target) {
		return n;
	}

	float direction = Mathf::Sign(target - n);
	n += alpha * deltaTime * direction;

	return (direction == Mathf::Sign(target - n)) ? n : target;
}

void PlayerController::Destroy() {
	Input::RemoveInputCallback(BindFunction(PlayerController::OnEvent, this), SDL_SCANCODE_W);
	Input::RemoveInputCallback(BindFunction(PlayerController::OnEvent, this), SDL_SCANCODE_A);
	Input::RemoveInputCallback(BindFunction(PlayerController::OnEvent, this), SDL_SCANCODE_S);
	Input::RemoveInputCallback(BindFunction(PlayerController::OnEvent, this), SDL_SCANCODE_D);
	Input::RemoveInputCallback(BindFunction(PlayerController::OnEvent, this), SDL_SCANCODE_SPACE);
}

