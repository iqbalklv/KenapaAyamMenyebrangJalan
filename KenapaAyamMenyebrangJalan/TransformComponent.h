#pragma once
#include "Components.h"
#include "Vector2D.h"
#include "TextureManager.h"

class TransformComponent : public Component {

public:

	Vector2D position;
	Vector2D velocity;

	int height = TextureManager::size;
	int width = TextureManager::size;
	int scale = TextureManager::scale;

	float speed = 3.0f;

	TransformComponent() {
		position.Zero();
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}
	
	void init() override {
		velocity.Zero();
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
	
};