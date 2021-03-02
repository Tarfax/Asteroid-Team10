#pragma once
#include <string>
#include <SDL.h>
#include <Structs/Vector2.h>
#include <map>

class TextureCoordinator {

public: 
	static void Init(SDL_Renderer* renderer);
	static SDL_Texture* LoadTexture(std::string textureId, Vector2& sizeOut);

private:

	static TextureCoordinator* instance;
	static TextureCoordinator* GetInstance() {
		return instance = (instance != nullptr) ? instance : new TextureCoordinator();
	}

	SDL_Renderer* renderer;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, Vector2> textureSize;
};

