#pragma once
#include <string>
#include <SDL.h>
#include <Structs/Vector2.h>
#include <Structs/Sprite.h>
#include <map>
#include <vector>

class TextureCoordinator {

public: 
	static void Init(SDL_Renderer* renderer);
	static Sprite* GetSpriteFromId(std::string textureId);
	static void Delete(Sprite* texture);

private:
	TextureCoordinator();
	static TextureCoordinator* instance;
	static TextureCoordinator* GetInstance() {
		return instance = (instance != nullptr) ? instance : new TextureCoordinator();
	}

	static Sprite* LoadTexture(std::string textureId);

	SDL_Renderer* renderer;

	std::map<std::string, int> spritesRefcount;
	std::map<std::string, Sprite*> sprites;
	std::map<std::string, SDL_Texture*> textures;

};