#include "Projectile.h"
#include "Math/Mathf.h"

GameObject* Projectile::GetInstance() {
	GameObject* gameObject = nullptr;

	gameObject = new GameObject();
	gameObject->Init();

	Projectile* projectile = gameObject->AddComponent<Projectile>();

	SpriteRenderer* spriteRenderer = gameObject->AddComponent<SpriteRenderer>();

	Sprite sprite;
	sprite.SetTexture(projectile->textureId);
	spriteRenderer->SetSprite(sprite);

	
	PositionWrapper* positionWrapper = gameObject->AddComponent<PositionWrapper>();
	positionWrapper->SetTexDimensions(spriteRenderer->GetRect());

	return gameObject;
}

void Projectile::Init() {

	transform = gameObject->GetComponent<Transform>();

	speed = 150;
	
}

void Projectile::SetDirection(Vector2 direction) {
	this->direction = direction;
}

void Projectile::Update(float deltaTime) {

	transform->Translate(Vector2((speed * deltaTime) * direction.X, (speed * deltaTime) * direction.Y));
	lifeTime -= deltaTime;
	if (lifeTime < 0.0f) {
		gameObject->Destroy();
	}
}

void Projectile::Destroy() {
	std::cout << "Projectile dead" << std::endl;
}
