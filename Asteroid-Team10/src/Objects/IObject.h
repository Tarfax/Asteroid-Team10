#pragma once
#include <SDL.h>

class IObject {
public:
	virtual void Init() = 0;
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;

	virtual void Draw(SDL_Renderer* renderer) = 0;

	virtual void Destroy() = 0;

};
