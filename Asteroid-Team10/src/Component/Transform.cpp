#include "Transform.h"
#include <iostream>
#include <Core/Engine.h>
#include <Math/Mathf.h>

void Transform::Init() {
	scale = Vector2(1);
	position = {0, 0};
	rotation = 90;
	//forward = {0, -1};
}

void Transform::Update(float deltaTime) {
	if (rotation < 0.0f) {
		rotation = 360.0f;
	}
	else if (rotation > 360.0f) {
		rotation = 0.0f;
	}

	forward.X = cos(Mathf::DegToRad2(Rotation()));
	forward.Y = sin(Mathf::DegToRad2(Rotation()));
}


void Transform::Destroy() { }

void Transform::Translate(Vector2 move) {
	position.X += move.X;
	position.Y += move.Y;
}