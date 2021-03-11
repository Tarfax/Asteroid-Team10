#include "GameObject.h"

int GameObject::nextId = 0;
std::map<int, GameObject*> GameObject::gameObjects;
std::map<int, GameObject*> GameObject::gameObjectsDisabled;
std::map<int, GameObject*> GameObject::gameObjectsToDestroy;

std::set<int> GameObject::gameObjectsToActivate;
std::set<int> GameObject::gameObjectsToDisable;
std::map<int, GameObject*> GameObject::gameObjectsToInit;

GameObject::GameObject(): id(nextId++) {
	transform = AddComponent<Transform>();
	collider = AddComponent<BoxCollider2D>();;
	gameObjectsToInit[id] = this;
}

void GameObject::OnInit() {
	gameObjectsDisabled[id] = this;
}

void GameObject::OnEnable() {
	for (IComponent* component : components) {
		component->OnEnable();
	}
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

void GameObject::OnDisable() {
	for (IComponent* component : components) {
		component->OnDisable();
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

void GameObject::SetActive(bool beActive) {
	if (beActive) {
		if (gameObjectsDisabled.count(id) == 1) {
			gameObjectsToActivate.emplace(id);
		}
	}
	else {
		if (gameObjects.count(id) == 1) {
			gameObjectsToDisable.emplace(id);
		}
	}
}

bool GameObject::IsActive() {
	return { gameObjects.count(id) == 1 || gameObjectsToActivate.count(id) == 1};
}

//Static stuff
void GameObject::Init() {
	std::map<int, GameObject*>::iterator it;
	for (it = gameObjectsToInit.begin(); it != gameObjectsToInit.end(); it++) {
		it->second->OnInit();
	}
	gameObjectsToInit.clear();
}

void GameObject::Enable() {
	std::map<int, GameObject*>::iterator it;
	for (int id : gameObjectsToActivate) {
		if (gameObjectsDisabled.count(id) == 0) continue;
		it = gameObjectsDisabled.find(id);
		it->second->OnEnable();
		gameObjects.insert(*it);
		gameObjectsDisabled.erase(it->second->id);
	}
	gameObjectsToActivate.clear();
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

void GameObject::Disable() {
	//Implement!: gameObjects to disable.
	std::map<int, GameObject*>::iterator it;
	for (int id : gameObjectsToDisable) {
		if (gameObjects.count(id) == 0) continue;
		it = gameObjects.find(id);
		it->second->OnDisable();
		gameObjectsDisabled.insert(*it);
		gameObjects.erase(it->second->id);
	}
	gameObjectsToDisable.clear();
}

void GameObject::Destroy(GameObject* gameObject) {
	gameObjectsToDestroy[gameObject->id] = gameObject;
}

void GameObject::CleanUp() {
	std::map<int, GameObject*>::iterator it;
	for (it = gameObjectsToDestroy.begin(); it != gameObjectsToDestroy.end(); it++) {
		it->second->OnDestroy();
		ClearOut(it);
		delete it->second;
	}
	gameObjectsToDestroy.clear();

	//for (int id : gameObjectsToDisable) {
	//	if (gameObjects.count(id) == 0) continue;
	//	it = gameObjects.find(id);
	//	gameObjectsDisabled.emplace(*it);
	//	gameObjects.erase(it->second->id);
	//}
	//gameObjectsToDisable.clear();

	//for (int id : gameObjectsToActivate) {
	//	if (gameObjectsDisabled.count(id) == 0) continue;
	//	it = gameObjectsDisabled.find(id);
	//	gameObjects.insert(*it);
	//	gameObjectsDisabled.erase(it->second->id);
	//}
	//gameObjectsToActivate.clear();

}

void GameObject::ClearOut(std::map<int, GameObject*>::iterator it) {
	gameObjects.erase(it->second->id);
	gameObjectsDisabled.erase(it->second->id);
	gameObjectsToActivate.erase(it->second->id);
	gameObjectsToDisable.erase(it->second->id);
}