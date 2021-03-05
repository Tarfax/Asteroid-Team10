#pragma once

#include "IObject.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <Component/Core/SpriteRenderer.h>
#include <Component/Core/BoxCollider2D.h>

//#include <Component/Transform.h>

class GameObject: public IObject {

public:
	GameObject();
	virtual void Init();
	virtual void Start() override {}
	virtual void Update(float deltaTime) override;

	virtual void Draw(SDL_Renderer* renderer) override;


	void Destroy();

public: //Static

	static void DoUpdate(float deltaTime);
	static void DoDraw(SDL_Renderer* renderer);
	static void DoDestroy(GameObject* gameObject);
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

	SpriteRenderer* spriteRenderer;
	BoxCollider2D* collider;
	Transform* transform;

	std::vector<IComponent*> components;

	static int nextId;
	static std::map<int, GameObject*> gameObjects;
	static std::map<int, GameObject*> gameObjectsToDestroy;

};