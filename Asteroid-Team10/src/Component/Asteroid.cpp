#include "Asteroid.h"
#include "Math/Mathf.h"
#include "Component/PositionWrapper.h"
#include "Component/Core/BoxCollider2D.h"
#include "Component/Core/SpriteRenderer.h"
#include <Structs/Sprite.h>
#include <FactorySystem/PredefinedObject.h>

#include <EventSystem/ObjectEvent.h>


std::unordered_map<int, GameObject*> Asteroid::activeObjects;
std::unordered_map<int, GameObject*> Asteroid::inactiveObjects;
std::vector<Asteroid::CallbackData> Asteroid::callbacks;

void Asteroid::Init() {
	gameObject->AddComponent<SpriteRenderer>();
	gameObject->AddComponent<PositionWrapper>();

	myGameObject = gameObject;
	myID = gameObject->id;

	speed = Mathf::RandomFloat() * 100.0f;
	rotationSpeed = Mathf::RandomFloat() * 100.0f;
	direction.X = Mathf::RandomFloat(-1, 1);
	direction.Y = Mathf::RandomFloat(-1, 1);
	direction.Normalize();
}

void Asteroid::SetData(ObjectData* data) {
	AsteroidData* asteroidData = dynamic_cast<AsteroidData*>(data);
	transform->Scale() = asteroidData->Scale;

	SpriteRenderer* spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
	spriteRenderer->SetSprite(Sprite::CreateSprite(data->TextureIds[0]));

	PositionWrapper* positionWrapper = gameObject->GetComponent<PositionWrapper>();
	positionWrapper->SetTexDimensions(spriteRenderer->GetRect());

	BoxCollider2D* collider = gameObject->GetComponent<BoxCollider2D>();
	collider->SetBounds(spriteRenderer->GetRect());
	collider->SetLayer(Layer::lAsteroid);
	collider->SetCollideWithLayer(Layer::lProjectile);

	AddToPool();
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

void Asteroid::Update(float deltaTime)
{
	transform->Translate(Vector2((speed * deltaTime) * direction.X, (speed * deltaTime) * direction.Y));
	transform->Rotation() += (double)rotationSpeed * (double)deltaTime;
}

void Asteroid::Destroy() { 
	ObjectDestroyedEvent event { gameObject };
	for (int i = 0; i < callbacks.size(); i++) {
		CallbackData data = callbacks[i];
		data.EventCallback(event);
	}
}


void Asteroid::AddToPool()
{
	if (inactiveObjects.count(myID) == 0) {
		inactiveObjects.insert(std::pair<int, GameObject*>(myID, myGameObject));

		// call to GameObject to add object to inactive container
	}
}

GameObject* Asteroid::GetFromPool() {
	if (inactiveObjects.empty()) return nullptr;

	GameObject* gameObject = inactiveObjects.begin()->second;

	gameObject->GetComponent<Asteroid>()->SetActive(true);

	return gameObject;
}

bool Asteroid::IsActive()
{
	return false;
	//return pooledObjecets[myGameObject];
}

void Asteroid::SetActive(bool setActive)
{
	if (setActive) {

		if (inactiveObjects.count(myID) == 1 && activeObjects.count(myID) == 0) {
			activeObjects.insert(std::pair<int, GameObject*>(myID, myGameObject));
			inactiveObjects.erase(myID);
		}
	}
	else {

		if (activeObjects.count(myID) == 1 && inactiveObjects.count(myID) == 0) {
			inactiveObjects.insert(std::pair<int, GameObject*>(myID, myGameObject));
			activeObjects.erase(myID);
		}
	}

}
