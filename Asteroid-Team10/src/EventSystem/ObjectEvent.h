#pragma once
#include <EventSystem/Event.h>
#include <sstream>
#include <Objects/GameObject.h>

class ObjectEvent: public Event {
public:
	GameObject* gameObject;

	EventClassCategory(EventCategoryGameObject)
protected:
	ObjectEvent(GameObject* gameObject)
		: gameObject(gameObject) { }

};

class ObjectDestroyedEvent: public ObjectEvent {
public:
	ObjectDestroyedEvent(GameObject* gameObject)
		: ObjectEvent(gameObject)
	{ 
	}

	EventClassType(ObjectDestroyed)

private:
	
};

class AsteroidDestroyedEvent: public ObjectDestroyedEvent {
public:
	AsteroidDestroyedEvent(GameObject* gameObject)
		: ObjectDestroyedEvent(gameObject)
	{
	}

	std::string ToString() const override {
		std::stringstream ss;
		ss << "AsteroidDestroyedEvent: " << gameObject->id << " (was destroyed)";
		return ss.str();
	}

	EventClassType(ObjectDestroyed)

private:
	int level;
	
	//Other stuff
	int sound;

};