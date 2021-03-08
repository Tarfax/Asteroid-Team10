#include "GameState.h"
#include "Component/Asteroid.h"

#define CreateFunctionCallback(x, y) std::bind(&x, y, std::placeholders::_1)

GameState::GameState() {
	Asteroid::AddCallback(CreateFunctionCallback(GameState::OnEvent, this));
}

void GameState::OnEvent(Event& e) {
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<ObjectDestroyedEvent>(CreateFunctionCallback(GameState::OnObjectDestroyed, this));
}

bool GameState::OnObjectDestroyed(ObjectDestroyedEvent& e) {
	std::cout << e.ToString() << std::endl;
	return false;
}
