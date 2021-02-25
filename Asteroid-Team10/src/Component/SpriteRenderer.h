#pragma once

#include <SDL.h>
#include <Component/IComponent.h>
#include <string>

class SpriteRenderer : IComponent {

public: 
	void Init();
	void Update(float deltaTime);
	void Destroy();

	void SetSprite(const std::string textureId);

	void Draw(SDL_Renderer* renderer);

	//Variables
private:

	std::string textureId;
	SDL_Texture* texture;

	//Methods
private: 


};