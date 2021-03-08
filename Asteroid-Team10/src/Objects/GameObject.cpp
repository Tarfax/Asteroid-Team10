#include "GameObject.h"

int GameObject::nextId = 0;
std::map<int, GameObject*> GameObject::gameObjects;
std::map<int, GameObject*> GameObject::gameObjectsInactive;
std::map<int, GameObject*> GameObject::gameObjectsToDestroy;

std::set<int> GameObject::gameObjectsToActivate;
std::set<int> GameObject::gameObjectsToInactivate;
std::map<int, GameObject*> GameObject::gameObjectsToInit;

GameObject::GameObject(): id(nextId++) {
	transform = AddComponent<Transform>();
	collider = AddComponent<BoxCollider2D>();;
	gameObjectsToInit[id] = this;
}

void GameObject::OnInit() {
	gameObjects[id] = this;
}

void GameObject::OnUpdate(float deltaTime) {
	for (IComponent* c : components) {
		c->Update(deltaTime);
	}
}

void GameObject::OnDraw(SDL_Renderer* renderer) {
	if (collider != nullptr) {
		collider->Draw(renderer, transform);
	}
}

void GameObject::SetActive(bool beActive) {
	if (beActive) {
		if (gameObjectsInactive.count(id) == 1) {
			gameObjectsToActivate.emplace(id);
		}
	}
	else {
		if (gameObjects.count(id) == 1) {
			gameObjectsToInactivate.emplace(id);
		}
	}
}

void GameObject::OnDestroy() {
	for (IComponent* component : components) {
		component->Destroy();
	}

	for (IComponent* component : components) {
		delete component;
	}
	
	components.clear();
}


//Static stuff
void GameObject::Init() {
	std::map<int, GameObject*>::iterator it;
	for (it = gameObjectsToInit.begin(); it != gameObjectsToInit.end(); it++) {
		it->second->OnInit();
	}
	gameObjectsToInit.clear();
}


void GameObject::Update(float deltaTime) {
	std::map<int, GameObject*>::iterator it;
	for (it = gameObjects.begin(); it != gameObjects.end(); it++) {
		it->second->OnUpdate(deltaTime);
	}
}

void GameObject::Draw(SDL_Renderer* renderer) {
	std::map<int, GameObject*>::iterator it;
	for (it = gameObjects.begin(); it != gameObjects.end(); it++) {
		it->second->OnDraw(renderer);
	}
}

void GameObject::Destroy(GameObject* gameObject) {
	gameObjectsToDestroy[gameObject->id] = gameObject;
}

void GameObject::CleanUp() {
	std::map<int, GameObject*>::iterator it;
	for (it = gameObjectsToDestroy.begin(); it != gameObjectsToDestroy.end(); it++) {
		it->second->OnDestroy();
		gameObjects.erase(it->second->id);
		delete it->second;
	}
	gameObjectsToDestroy.clear();

	for (int id : gameObjectsToInactivate) {
		it = gameObjects.find(id);
		gameObjectsInactive.emplace(*it);
		gameObjects.erase(it);
	}
	gameObjectsToInactivate.clear();

	for (int id : gameObjectsToActivate) {
		it = gameObjectsInactive.find(id);
		gameObjects.insert(*it);
		gameObjectsInactive.erase(it);
	}
	gameObjectsToActivate.clear();

}