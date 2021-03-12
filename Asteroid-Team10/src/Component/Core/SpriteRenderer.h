#pragma once

#include <SDL.h>
#include <string>

#include <Structs/Vector2.h>
#include <Structs/Sprite.h>

#include <Component/Core/Renderer.h>
#include <Component/Core/Transform.h>



class SpriteRenderer: public Renderer {

public:
	SpriteRenderer(GameObject* gameObject) : Renderer(gameObject) { }
	void Init();
	void Enable() override {}
	void Update(float deltaTime);
	void Disable() override {}
	void Destroy();

	void SetSprite(Sprite* sprite);

	void OnDraw(SDL_Renderer* renderer);

	SDL_Rect GetRect();

	//Variables
private:
	/*Vector2 textureSize;
	std::string textureId;
	SDL_Texture* texture;*/
	Sprite* sprite;

	//Methods
private:


};