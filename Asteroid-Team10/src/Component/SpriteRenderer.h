#pragma once

#include <SDL.h>
#include <Component/IComponent.h>
#include <string>
#include <Component/Transform.h>
#include <Structs/Vector2.h>

class SpriteRenderer : IComponent {

public: 
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