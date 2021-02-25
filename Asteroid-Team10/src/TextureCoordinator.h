#pragma once
#include <string>
#include <SDL.h>
#include <Structs/Vector2.h>

class TextureCoordinator {

public: 
	static void Init(SDL_Renderer* renderer);
	static SDL_Texture* LoadTexture(std::string textureId, Vector2& sizeOut);

private:

	static TextureCoordinator* intance;
	static TextureCoordinator* GetInstance() {
		return intance = (intance != nullptr) ? intance : new TextureCoordinator();
	}

	SDL_Renderer* renderer;

};

