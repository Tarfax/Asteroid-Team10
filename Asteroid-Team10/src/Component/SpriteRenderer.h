#pragma once

#include <SDL.h>
#include <string>

#include <Structs/Vector2.h>

#include <Component/IComponent.h>
#include <Component/Transform.h>

class SpriteRenderer: public IComponent {

public:
	SpriteRenderer(GameObject* gameObject) : IComponent(gameObject) { }
	void Init();
	void Update(float deltaTime);
	void Destroy();

	void SetSprite(const std::string textureId);

	void Draw(SDL_Renderer* renderer, Transform* transform);

	//Variables
private:
	Vector2 textureSize;

	std::string textureId;
	SDL_Texture* texture;

	//Methods
private:


};