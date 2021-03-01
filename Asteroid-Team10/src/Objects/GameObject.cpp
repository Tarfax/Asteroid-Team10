#include "GameObject.h"

int GameObject::nextId = 0;
std::map<int, GameObject*> GameObject::gameObjects;
std::map<int, GameObject*> GameObject::gameObjectsToDestroy;

GameObject::GameObject() {
	id = nextId++;
	gameObjects[id] = this;
	spriteRenderer = nullptr;
}

void GameObject::Init() {
	transform = AddComponent<Transform>();
}

void GameObject::Update(float deltaTime) {
	for (IComponent* c : components) {
		c->Update(deltaTime);
	}
}

void GameObject::Draw(SDL_Renderer* renderer) {
	if (spriteRenderer == nullptr) {
		spriteRenderer = GetComponent<SpriteRenderer>();
	}
	spriteRenderer->Draw(renderer, transform);
}

void GameObject::Destroy() {
	for (IComponent* component : components) {
		component->Destroy();
		delete component;
	}
	components.clear();
}

//Static stuff
void GameObject::DoUpdate(float deltaTime) {
	std::map<int, GameObject*>::iterator it;
	for (it = gameObjects.begin(); it != gameObjects.end(); it++) {
		it->second->Update(deltaTime);
	}
}

void GameObject::DoDraw(SDL_Renderer* renderer) {
	std::map<int, GameObject*>::iterator it;
	for (it = gameObjects.begin(); it != gameObjects.end(); it++) {
		it->second->Draw(renderer);
	}
}

void GameObject::DoDestroy(GameObject* gameObject) {
	//std::cout << "GameObject::DoDestroy()" << std::endl;

	gameObjectsToDestroy[gameObject->id] = gameObject;
}

void GameObject::CleanUp() {
	std::map<int, GameObject*>::iterator it;
	for (it = gameObjectsToDestroy.begin(); it != gameObjectsToDestroy.end(); it++) {
		it->second->Destroy();
		gameObjects.erase(it->second->id);
		//std::cout << "Cleaning " << it->second->id << std::endl;
		//std::cout << "size() " << sizeof(gameObjects) << std::endl;
		delete it->second;
	}
	gameObjectsToDestroy.clear();


}