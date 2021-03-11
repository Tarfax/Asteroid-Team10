#include "Asteroid.h"
#include "Math/Mathf.h"
#include "Component/PositionWrapper.h"
#include "Component/Core/BoxCollider2D.h"
#include "Component/Core/SpriteRenderer.h"
#include <Structs/Sprite.h>
#include <FactorySystem/PredefinedObject.h>

#include <EventSystem/ObjectEvent.h>
#include <Core/Input.h>


//std::unordered_map<int, GameObject*> Asteroid::activeObjects;
//std::unordered_map<int, GameObject*> Asteroid::inactiveObjects;
std::vector<Asteroid::CallbackData> Asteroid::callbacks;

void Asteroid::Init() {
	gameObject->AddComponent<SpriteRenderer>();
	gameObject->AddComponent<PositionWrapper>();

	//myGameObject = gameObject;
	//myID = gameObject->id;

	//speed = Mathf::RandomFloat() * 100.0f;

}


void Asteroid::SetData(ObjectData* data) {
	AsteroidData* asteroidData = dynamic_cast<AsteroidData*>(data);
	transform->Scale() = asteroidData->Scale;

	speed = Mathf::RandomFloat(asteroidData->MinSpeed, asteroidData->MaxSpeed);


	level = asteroidData->Level;

	SpriteRenderer* spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
	spriteRenderer->SetSprite(Sprite::CreateSprite(data->TextureIds[0]));

	PositionWrapper* positionWrapper = gameObject->GetComponent<PositionWrapper>();
	positionWrapper->SetTexDimensions(spriteRenderer->GetRect());

	BoxCollider2D* collider = gameObject->GetComponent<BoxCollider2D>();
	collider->SetBounds(spriteRenderer->GetRect());
	collider->SetLayer(Layer::lAsteroid);
	collider->SetCollideWithLayer(Layer::lProjectile);

	rotationSpeed = Mathf::RandomFloat() * 10.0f;
	direction.X = Mathf::RandomFloat(-1, 1);
	direction.Y = Mathf::RandomFloat(-1, 1);
	direction.Normalize();

	transform->Rotation() = Mathf::RandomFloat(0,360);

	//AddToPool();
}

void Asteroid::AddCallback(const EventCallbackFunc& callback) {
	callbacks.emplace_back(callback);
}

void Asteroid::RemoveCallback(const EventCallbackFunc& callback) {
	for (int i = 0; i < callbacks.size(); i++) {
		if (callbacks[i].EventCallback.target_type().hash_code() == callback.target_type().hash_code()) {
			callbacks.erase(callbacks.begin() + i);
			return;
		}
	}
}

void Asteroid::OnEnable() { }

void Asteroid::Update(float deltaTime)
{
	transform->Translate(Vector2((speed * deltaTime) * direction.X, (speed * deltaTime) * direction.Y));
	transform->Rotation() += (double)rotationSpeed * (double)deltaTime;

	if (Input::GetKeyDown(SDL_SCANCODE_K)) {
		std::cout << "Kill?" << std::endl;
	}
}

void Asteroid::OnDisable() {
	AsteroidDestroyedEvent event = { gameObject, level };
	for (int i = 0; i < callbacks.size(); i++) {
		CallbackData data = callbacks[i];
		data.EventCallback(event);
	}
}

void Asteroid::Destroy() {
	//AsteroidDestroyedEvent event = {gameObject, level};
	//for (int i = 0; i < callbacks.size(); i++) {
	//	CallbackData data = callbacks[i];
	//	data.EventCallback(event);
	//}
}