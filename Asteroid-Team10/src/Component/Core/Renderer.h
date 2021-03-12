#pragma once

#include <Objects/GameObject.h>
#include <Component/Core/IComponent.h>
#include <Component/Core/Transform.h>
#include <vector>

//class GameObject;

class Renderer: public IComponent {
public: 
	static void Draw(SDL_Renderer* renderer);
protected:

	Renderer(GameObject* gameObject);

	~Renderer();

	virtual void OnDraw(SDL_Renderer* renderer) = 0;

	Transform* transform;

private:
	void OnEnable() override;
	void OnDisable() override;

	virtual void Enable()= 0;
	virtual void Disable()= 0;
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Destroy() = 0;


	static std::vector<Renderer*> renderers;
};