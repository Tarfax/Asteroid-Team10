#pragma once

#include "IObject.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <Component/Core/Renderer.h>
#include <Component/Core/BoxCollider2D.h>

//#include <Component/Transform.h>
class Renderer;
class GameObject: public IObject {

public:
	GameObject();
	void OnInit();
	void OnStart() override {}
	void OnUpdate(float deltaTime) override;
	void OnDraw(SDL_Renderer* renderer) override;
	void OnDestroy() override;


	void SetActive(bool beActive);


public: //Static

	static void Init();
	static void Update(float deltaTime);
	static void Draw(SDL_Renderer* renderer);
	static void Destroy(GameObject* gameObject);
	static void CleanUp();


public: //Components

	template <typename T, typename = std::enable_if_t<std::is_base_of<IComponent, T>::value>>
	T* AddComponent() {
		T* component = new T(this);

		component->Init();
		components.push_back(component);
		return component;
	}

	template <typename T, typename = std::enable_if_t<std::is_base_of<IComponent, T>::value>>
	T* GetComponent() {
		for (IComponent* component : components) {
			if (typeid(T) == typeid(*component)) {
				return (T*)component;
			}
		}
		return nullptr;
	}



	const int id;
private:

	Renderer* renderer;
	BoxCollider2D* collider;
	Transform* transform;

	std::vector<IComponent*> components;

	static int nextId;
	static std::map<int, GameObject*> gameObjects;
	static std::map<int, GameObject*> gameObjectsInactive;
	static std::map<int, GameObject*> gameObjectsToDestroy;

	static std::set<int> gameObjectsToActivate;
	static std::set<int> gameObjectsToInactivate;

	static std::map<int, GameObject*> gameObjectsToInit;

};