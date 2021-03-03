#include "Asteroid.h"
#include "Math/Mathf.h"
#include "Component/PositionWrapper.h"
#include "Component/Core/BoxCollider2D.h"
#include <Structs/Sprite.h>

std::list<GameObject*> Asteroid::activeObjecets{};
std::list<GameObject*> Asteroid::inactiveObjecets{};

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

GameObject* Asteroid::GetInstance()
{
	GameObject* gameObject = nullptr;
	
	gameObject = new GameObject();
	gameObject->Init();

	Asteroid* asteroid = gameObject->AddComponent<Asteroid>();

	asteroid->myGameObject = gameObject;

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

	//temp
	asteroid->AddToPool();
	asteroid->SetActive(false);
	//end temp

	return gameObject;
}

void Asteroid::AddToPool()
{
	std::cout << "Asteroid->AddToPool: adding object " << myGameObject << '\n';
	inactiveObjecets.push_back(myGameObject);
}

void Asteroid::SetActive(bool setActive)
{
	if (setActive) {
		for (GameObject* gObj : activeObjecets)
		{
			if (myGameObject == gObj) {
				std::cout << "Asteroid->SetActive(true): couldn't add object to 'activeObjects': it already exists!\n";
				return;
			}
		}
		activeObjecets.push_back(myGameObject);
		inactiveObjecets.remove(myGameObject);

		// debugging
		std::cout << "Asteroid->SetActive(true): activating object " << myGameObject << '\n';
		std::cout << "Asteroid->SetActive(true): listSize: " << activeObjecets.size() << '\n';
		std::cout << "Asteroid->SetActive(true): list: ";

		for (GameObject* gObj : activeObjecets)
		{
			std::cout << gObj << ", ";
		}
		std::cout << '\n';
		std::cout << '\n';
		//end debugging
	}
	else {
		for (GameObject* gObj : inactiveObjecets)
		{
			if (myGameObject == gObj) {
				std::cout << "Asteroid->SetActive(false): couldn't add object to 'inactiveObjects': it already exists!\n";
				return;
			}
		}

		inactiveObjecets.push_back(myGameObject);
		activeObjecets.remove(myGameObject);

		// debugging
		std::cout << "Asteroid->SetActive(false): deactivating object " << myGameObject << '\n';
		std::cout << "Asteroid->SetActive(false): listSize: " << inactiveObjecets.size() << '\n';
		std::cout << "Asteroid->SetActive(false): list: ";

		for (GameObject* gObj : inactiveObjecets)
		{
			std::cout << gObj << ", ";
		}
		std::cout << '\n';
		std::cout << '\n';
		//end debugging
	}
}
