#include "Projectile.h"
#include "Math/Mathf.h"
#include "Structs/Sprite.h"

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

Projectile::~Projectile() {
	//std::cout << "DESTRUCTION: ~Projectile()" << std::endl;
}

void Projectile::Init() {

	transform = gameObject->GetComponent<Transform>();

	speed = 350;

}

void Projectile::SetDirection(Vector2 direction) {
	this->direction = direction;
}

void Projectile::Update(float deltaTime) {

	transform->Translate(Vector2((speed * deltaTime) * direction.X, (speed * deltaTime) * direction.Y));

	std::cout << "HELLO?" << std::endl;
	lifeTime -= deltaTime;
	if (lifeTime < 0.0f) {
		GameObject::DoDestroy(gameObject);
		lifeTime = 10000;
	}
}

void Projectile::Destroy() {
	//std::cout << "Projectile is about to be dead" << std::endl;
}
