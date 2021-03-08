#include "Renderer.h"

std::vector<Renderer*> Renderer::renderers;

Renderer::Renderer(GameObject* gameObject): IComponent(gameObject) {
	renderers.push_back(this);
	transform = gameObject->GetComponent<Transform>();
}

Renderer::~Renderer() {
	for (int i = 0; i < renderers.size(); i++) {
		if (renderers[i] == this) {
			renderers.erase(renderers.begin() + i);
			break;
		}
	}
}

void Renderer::Draw(SDL_Renderer* renderer) {
	for (int i = 0; i < renderers.size(); i++) {
		renderers[i]->OnDraw(renderer);
	}
}
