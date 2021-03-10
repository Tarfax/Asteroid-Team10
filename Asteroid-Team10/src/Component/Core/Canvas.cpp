#include "Component/Core/Canvas.h"
#include <Structs/Sprite.h>

void Canvas::Init() {

}

void Canvas::Update(float deltaTime) {
	for (int i = 0; i < elements.size(); i++) {
		elements[i]->Update(deltaTime);
	}
}

void Canvas::Destroy() {
	for (int i = 0; i < elements.size(); i++) 	{
		elements[i]->Destroy();
	}
	for (int i = 0; i < elements.size(); i++) {
		delete elements[i];
	}
	elements.clear();
}

void Canvas::AddUIElement(UIElement* element) {
	elements.push_back(element);
}


void Canvas::OnDraw(SDL_Renderer* renderer) {

	for (int i = 0; i < elements.size(); i++) {
		UIElement& element = *elements[i];
		SDL_Texture* texture = element.GetSprite()->Texture;
		SDL_Rect& source = element.GetSprite()->Rect;
		SDL_Rect destination = element.GetPosition();
		SDL_RenderCopyEx(renderer, texture, &source, &destination, 0, nullptr, SDL_FLIP_NONE);
	}

}
