#pragma once
#include <SDL.h>
#include <Structs/Sprite.h>
#include <iostream>

class UIElement {

public:
	virtual ~UIElement() {
		//std::cout << "UI Element " << sprite->TextureId << " gone " << std::endl;
	}

	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Destroy() = 0;

	void SetPosition(Vector2 position) { this->position.x = position.X; this->position.y = position.Y; }
	void SetPosition(int x, int y) { this->position.x = x; this->position.y = y;}
	void SetSize(Vector2 size) { this->position.w = size.X; this->position.h = size.Y; }

	/// <summary>
	/// Sets the size to the sprite's size.
	/// </summary>
	void SetSize() { this->position.w = sprite->Size.X; this->position.h = sprite->Size.Y; }
	SDL_Rect GetPosition() const { return position; }
	Sprite* GetSprite() const { return sprite; }

protected:
	SDL_Rect position;
	Sprite* sprite;

};