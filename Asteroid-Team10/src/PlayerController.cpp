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

PlayerController* PlayerController::playerController = nullptr;

void PlayerController::Init() {
	if (playerController == nullptr) {
		playerController = this;

		rotationSpeed = 120.0f;
		targetSpeed = speed;

		acceleration = 100.0f;
		fireRate = 0.14f;
		momentumAcceleration = 1;
		transform = gameObject->GetComponent<Transform>();

		SpriteRenderer* renderer = gameObject->AddComponent<SpriteRenderer>();
		PositionWrapper* positionWrapper = gameObject->AddComponent<PositionWrapper>();

		Input::AddInputCallback(CreateFunctionCallback(PlayerController::OnEvent, this), SDL_SCANCODE_W);
		Input::AddInputCallback(CreateFunctionCallback(PlayerController::OnEvent, this), SDL_SCANCODE_A);
		Input::AddInputCallback(CreateFunctionCallback(PlayerController::OnEvent, this), SDL_SCANCODE_S);
		Input::AddInputCallback(CreateFunctionCallback(PlayerController::OnEvent, this), SDL_SCANCODE_D);
		Input::AddInputCallback(CreateFunctionCallback(PlayerController::OnEvent, this), SDL_SCANCODE_SPACE);
	}
}


void PlayerController::SetData(ObjectData* data) {
	PlayerData* playerData = dynamic_cast<PlayerData*>(data);
	speed = playerData->Speed;
	rotationSpeed = playerData->RotationSpeed;

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
	dispatcher.Dispatch<KeyPressedEvent>(CreateFunctionCallback(PlayerController::OnKeyPressedEvent, this));
}

bool PlayerController::OnKeyPressedEvent(KeyPressedEvent& e) {
	static int counter = 0;
	counter++;
	if (e.GetKeyCode() == SDL_SCANCODE_W) {
		//std::cout << "W was pressed\n";
		targetSpeed = speed;

		momentum.X = IncrementTowards(momentum.X, transform->forward.X, momentumAcceleration, e.GetDeltaTime());
		momentum.Y = IncrementTowards(momentum.Y, transform->forward.Y, momentumAcceleration, e.GetDeltaTime());
		//currentSpeed = IncrementTowards(currentSpeed, targetSpeed, acceleration, e.GetDeltaTime());
	}

	if (e.GetKeyCode() == SDL_SCANCODE_A) {
		transform->Rotation() -= (double)(rotationSpeed * e.GetDeltaTime());
		//std::cout << "A was pressed " << counter << " deltaTime: " << e.GetDeltaTime() << "\n";
	}

	if (e.GetKeyCode() == SDL_SCANCODE_S) {
		//std::cout << "S was pressed\n";
		targetSpeed = -speed;

		momentum.X = IncrementTowards(momentum.X, transform->forward.X, momentumAcceleration, e.GetDeltaTime());
		momentum.Y = IncrementTowards(momentum.Y, transform->forward.Y, momentumAcceleration, e.GetDeltaTime());
	}

	if (e.GetKeyCode() == SDL_SCANCODE_D) {
		transform->Rotation() += (double)(rotationSpeed * e.GetDeltaTime());
		//std::cout << "D was pressed " << counter << "\n";
	}

	if (e.GetKeyCode() == SDL_SCANCODE_SPACE) {
		if (fireRateTimer <= 0.0f) {
			Fire();
			fireRateTimer = fireRate;
		}
	}

	return true;
}

void PlayerController::Update(float deltaTime) {

	currentSpeed = IncrementTowards(currentSpeed, targetSpeed, acceleration, deltaTime);
	targetSpeed = currentSpeed * 0.9999f;

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
	GameObject* gameObject = Factory::GetInstance<Projectile>(Predef::Projectile);

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

	Projectile* projectile = gameObject->GetComponent<Projectile>();
	projectile->SetDirection(this->transform->forward);
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
	Input::RemoveInputCallback(CreateFunctionCallback(PlayerController::OnEvent, this), SDL_SCANCODE_W);
	Input::RemoveInputCallback(CreateFunctionCallback(PlayerController::OnEvent, this), SDL_SCANCODE_A);
	Input::RemoveInputCallback(CreateFunctionCallback(PlayerController::OnEvent, this), SDL_SCANCODE_S);
	Input::RemoveInputCallback(CreateFunctionCallback(PlayerController::OnEvent, this), SDL_SCANCODE_D);
	Input::RemoveInputCallback(CreateFunctionCallback(PlayerController::OnEvent, this), SDL_SCANCODE_SPACE);
}

