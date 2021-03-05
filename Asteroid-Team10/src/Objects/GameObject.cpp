#include "GameObject.h"

int GameObject::nextId = 0;
std::map<int, GameObject*> GameObject::gameObjects;
std::map<int, GameObject*> GameObject::gameObjectsToDestroy;

GameObject::GameObject() : id(nextId++) {
	//id = nextId++;
	gameObjects[id] = this;
	transform = AddComponent<Transform>();
	spriteRenderer = AddComponent<SpriteRenderer>();
	collider = AddComponent<BoxCollider2D>();;
}

void GameObject::Init() { }

void GameObject::Update(float deltaTime) {
	for (IComponent* c : components) {
		c->Update(deltaTime);
	}

	collider->Set(transform->X(), transform->Y(), transform->Scale());
}

void GameObject::Draw(SDL_Renderer* renderer) {
	spriteRenderer->Draw(renderer, transform);
	collider->Draw(renderer, transform);
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
	gameObjectsToDestroy[gameObject->id] = gameObject;
}

void GameObject::CleanUp() {
	std::map<int, GameObject*>::iterator it;
	for (it = gameObjectsToDestroy.begin(); it != gameObjectsToDestroy.end(); it++) {
		it->second->Destroy();
		gameObjects.erase(it->second->id);
		delete it->second;
	}
	gameObjectsToDestroy.clear();


}