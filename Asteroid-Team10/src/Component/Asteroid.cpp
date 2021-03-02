#include "Asteroid.h"
#include "Math/Mathf.h"
#include "Component/PositionWrapper.h"
#include "Component/Core/BoxCollider2D.h"
#include <Structs/Sprite.h>

void Asteroid::Init() {
	speed = Mathf::RandomFloat() * 100.0f;
	rotationSpeed = Mathf::RandomFloat() * 100.0f;
	direction.X = Mathf::RandomFloat();
	direction.Y = Mathf::RandomFloat();
	direction.Normalize();
	transform->Scale() = Mathf::RandomFloat();
	std::cout << Mathf::RandomFloat() << '\n';
}

void Asteroid::Update(float deltaTime)
{
	transform->Translate(Vector2((speed * deltaTime) * direction.X, (speed * deltaTime) * direction.Y));
	transform->Rotation() += (double)rotationSpeed * (double)deltaTime;
}

void Asteroid::Destroy() { }

GameObject* Asteroid::CreateInstance()
{
	GameObject* gameObject = nullptr;
	
	gameObject = new GameObject();
	gameObject->Init();

	Asteroid* asteroid = gameObject->AddComponent<Asteroid>();

	Sprite sprite;
	sprite.SetTexture(asteroid->textureID);

	SpriteRenderer* spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
	spriteRenderer->SetSprite(sprite);

	PositionWrapper* positionWrapper = gameObject->AddComponent<PositionWrapper>();
	positionWrapper->SetTexDimensions(spriteRenderer->GetRect());

	BoxCollider2D* collider = gameObject->GetComponent<BoxCollider2D>();
	collider->SetBounds(spriteRenderer->GetRect());

	std::cout << collider->GetBounds().w << " " << collider->GetBounds().h << std::endl;

	collider->SetLayer(Layer::lAsteroid);
	collider->SetCollideWithLayer(Layer::lProjectile);

	return gameObject;
}
