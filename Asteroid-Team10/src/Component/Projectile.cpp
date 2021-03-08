#include "Projectile.h"
#include "Math/Mathf.h"
#include "Structs/Sprite.h"
#include <Component/Core/BoxCollider2D.h>
#include <Component/Core/SpriteRenderer.h>

GameObject* Projectile::GetInstance() {
	GameObject* gameObject = nullptr;

	gameObject = new GameObject();
	//gameObject->OnInit();


	return gameObject;
}

Projectile::~Projectile() {
	//std::cout << "DESTRUCTION: ~Projectile()" << std::endl;
}

void Projectile::Init() {

	SpriteRenderer* spriteRenderer = gameObject->AddComponent<SpriteRenderer>();

	spriteRenderer->SetSprite(Sprite::CreateSprite(textureId));

	PositionWrapper* positionWrapper = gameObject->AddComponent<PositionWrapper>();
	positionWrapper->SetTexDimensions(spriteRenderer->GetRect());

	BoxCollider2D* collider = gameObject->GetComponent<BoxCollider2D>();
	collider->SetBounds(spriteRenderer->GetRect());
	collider->SetLayer(Layer::lProjectile);
	collider->SetCollideWithLayer(Layer::lAsteroid);

	speed = 450;
	transform->Scale() *= 0.2f;
}

void Projectile::SetDirection(Vector2 direction) {
	this->direction = direction;
}

void Projectile::Update(float deltaTime) {

	transform->Translate(Vector2((speed * deltaTime) * direction.X, (speed * deltaTime) * direction.Y));

	lifeTime -= deltaTime;
	if (lifeTime < 0.0f) {
		GameObject::Destroy(gameObject);
		lifeTime = 10000;
	}
}

void Projectile::Destroy() { }
