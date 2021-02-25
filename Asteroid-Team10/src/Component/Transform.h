#pragma once

#include <Structs/Vector2.h>
#include <Component/IComponent.h>

class Transform: public IComponent {
public:
	Vector2& Position() { return position; }
	double& Rotation() { return rotation; }
	Vector2& Scale() { return scale; }

	float& X() { return position.X; }
	float& Y() { return position.Y; }

	void Init() override;
	void Update(float deltaTime) override;
	void Destroy() override;

private:
	Vector2 position;
	double rotation;
	Vector2 scale;
};