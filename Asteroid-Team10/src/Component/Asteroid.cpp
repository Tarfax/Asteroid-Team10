#include "Asteroid.h"
#include "Math/Mathf.h"
#include "Component/PositionWrapper.h"
#include "Component/Core/BoxCollider2D.h"
#include <Structs/Sprite.h>

std::unordered_map<int, GameObject*> Asteroid::activeObjects { };
std::unordered_map<int, GameObject*> Asteroid::inactiveObjects { };

GameObject* Asteroid::GetInstance()
{
	GameObject* gameObject = nullptr;

	gameObject = new GameObject();
	gameObject->Init();

	Asteroid* asteroid = gameObject->AddComponent<Asteroid>();

	asteroid->myGameObject = gameObject;
	asteroid->myID = gameObject->id;

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

	asteroid->AddToPool();

	return gameObject;
}

void Asteroid::Init() {
	static int spawnedAsteroids;
	spawnedAsteroids++;

	speed = Mathf::RandomFloat() * 100.0f;
	rotationSpeed = Mathf::RandomFloat() * 100.0f;
	direction.X = Mathf::RandomFloat();
	direction.Y = Mathf::RandomFloat();
	direction.Normalize();
	transform->Scale() = Mathf::RandomFloat();

	if (spawnedAsteroids == 1) {
		asteroid1 = GetInstance();
		asteroid2 = GetInstance();
		asteroid3 = GetInstance();
		asteroid4 = GetInstance();
		asteroid5 = GetInstance();
		asteroid6 = GetInstance();
		std::cout << asteroid2->id << std::endl;

	}

}

void Asteroid::Update(float deltaTime)
{
	static int counter;
	counter++;
	transform->Translate(Vector2((speed * deltaTime) * direction.X, (speed * deltaTime) * direction.Y));
	transform->Rotation() += (double)rotationSpeed * (double)deltaTime;
		std::cout << gameObject->id << std::endl;

	if (counter > 1000) {
		if (asteroid6 != nullptr) {
			asteroid6->SetActive(false);
			asteroid4->SetActive(false);
			asteroid5->SetActive(false);
			asteroid1->SetActive(false);
			asteroid3->SetActive(false);
			//gameObject->SetActive(false);
		}
	}
}

void Asteroid::Destroy() { }


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
