#include "Projectile.h"
#include "Math/Mathf.h"
#include "Structs/Sprite.h"
#include <Component/Core/BoxCollider2D.h>

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

	BoxCollider2D* collider = gameObject->AddComponent<BoxCollider2D>();
	collider->SetBounds(spriteRenderer->GetRect());
	collider->SetLayer(Layer::lProjectile);
	collider->SetCollideWithLayer(Layer::lAsteroid);

	return gameObject;
}

Projectile::~Projectile() {
	//std::cout << "DESTRUCTION: ~Projectile()" << std::endl;
}

void Projectile::Init() {
	speed = 350;
	transform->Scale() * 0.2f;
}

void Projectile::SetDirection(Vector2 direction) {
	this->direction = direction;
}

void Projectile::Update(float deltaTime) {

	transform->Translate(Vector2((speed * deltaTime) * direction.X, (speed * deltaTime) * direction.Y));

	lifeTime -= deltaTime;
	if (lifeTime < 0.0f) {
		GameObject::DoDestroy(gameObject);
		lifeTime = 10000;
	}
}

void Projectile::Destroy() {
	//std::cout << "Projectile is about to be dead" << std::endl;
}
