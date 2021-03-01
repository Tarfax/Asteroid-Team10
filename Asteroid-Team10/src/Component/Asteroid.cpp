#include "Asteroid.h"
#include "Objects/GameObject.h"
#include "Math/Mathf.h"
#include "Component/PositionWrapper.h"
#include <iostream>
#include <Structs/Sprite.h>

void Asteroid::Init()
{
	transform = gameObject->GetComponent<Transform>();
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

void Asteroid::Destroy()
{
}

GameObject* Asteroid::CreateInstance()
{
	GameObject* gameObject = nullptr;
	
	gameObject = new GameObject();
	gameObject->Init();

	Asteroid* asteroid = gameObject->AddComponent<Asteroid>();
	SpriteRenderer* spriteRenderer = gameObject->AddComponent<SpriteRenderer>();

	Sprite sprite;
	sprite.SetTexture(asteroid->textureID);
	spriteRenderer->SetSprite(sprite);

	PositionWrapper* positionWrapper = gameObject->AddComponent<PositionWrapper>();
	positionWrapper->SetTexDimensions(spriteRenderer->GetRect());

	

	return gameObject;
}
