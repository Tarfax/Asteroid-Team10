#include "Projectile.h"
#include "Math/Mathf.h"
#include "Structs/Sprite.h"
#include <Component/Core/BoxCollider2D.h>
#include <Component/Core/SpriteRenderer.h>

Projectile::~Projectile() { }

void Projectile::Init() {
	gameObject->AddComponent<SpriteRenderer>();
	gameObject->AddComponent<PositionWrapper>();
}

void Projectile::OnEnable() { }

void Projectile::SetData(ObjectData* data) {
	ProjectileData* projectileData = dynamic_cast<ProjectileData*>(data);
	speed = projectileData->Speed;
	lifeTime = projectileData->LifeTime;
	lifeTimeCounter = lifeTime;

	SpriteRenderer* renderer = gameObject->GetComponent<SpriteRenderer>();
	renderer->SetSprite(Sprite::CreateSprite(data->TextureIds[0]));

	PositionWrapper* positionWrapper = gameObject->GetComponent<PositionWrapper>();
	positionWrapper->SetTexDimensions(renderer->GetRect());

	BoxCollider2D* collider = gameObject->GetComponent<BoxCollider2D>();
	collider->SetBounds(renderer->GetRect());
	collider->SetLayer(Layer::lProjectile);
	collider->SetCollideWithLayer(Layer::lAsteroid);

	transform->Scale() *= projectileData->Scale;
}

void Projectile::SetDirection(Vector2 direction) {
	this->direction = direction;
}

void Projectile::Update(float deltaTime) {
	transform->Translate(Vector2((speed * deltaTime) * direction.X, (speed * deltaTime) * direction.Y));

	lifeTimeCounter -= deltaTime;
	if (lifeTimeCounter < 0.0f) {
		//GameObject::Destroy(gameObject);
		gameObject->SetActive(false);
		lifeTimeCounter = lifeTime;
	}
}

void Projectile::OnDisable() { }

void Projectile::Destroy() { }
