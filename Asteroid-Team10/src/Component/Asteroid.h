#pragma once
#include "Component/Behaviour/Behaviour.h"
#include <unordered_map>
#include <vector>
#include <FactorySystem/FactoryObject.h>
#include <FactorySystem/Factory.h>
#include <functional>
#include <EventSystem/Event.h>

class Asteroid: public Behaviour, public FactoryObject {
	using EventCallbackFunc = std::function<void(Event&)>;

public:
	Asteroid(GameObject* gameObject): Behaviour(gameObject) {}

	void Init() override;
	void Update(float deltaTime) override;
	void Destroy() override;

	void SetData(ObjectData* data) override;
private:

	float speed { };
	float rotationSpeed { };
	Vector2 direction { };
	int level;

public: //Event System
	static void AddCallback(const EventCallbackFunc& callback);
	static void RemoveCallback(const EventCallbackFunc& callback);

private: //Event System

	struct CallbackData {
		CallbackData() { }
		CallbackData(EventCallbackFunc callback): EventCallback(callback) { }

		EventCallbackFunc EventCallback;
	};

	static std::vector<CallbackData> callbacks;



private: // object pool stuff

	static std::unordered_map<int, GameObject*> activeObjects;
	static std::unordered_map<int, GameObject*> inactiveObjects;

	GameObject* myGameObject;
	int myID;

	void AddToPool();
	bool IsActive();

public:
	static GameObject* GetFromPool();
	void SetActive(bool activeState);
};