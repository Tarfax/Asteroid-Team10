#pragma once

#include <Component/Core/Renderer.h>
#include <UI/UIElement.h>

class Canvas : public Renderer {

public:
	Canvas(GameObject* gameObject) : Renderer(gameObject) { }

	void OnDraw(SDL_Renderer* renderer) override;
	void Init() override;
	void OnEnable() override {}
	void Update(float deltaTime) override;
	void OnDisable() override {}
	void Destroy() override;

	void AddUIElement(UIElement* element);
	void RemoveUIElement(UIElement* element);

private:
	std::vector<UIElement*> elements;
};