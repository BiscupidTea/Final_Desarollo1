#pragma once
#include "tools/tools.h"

#include "Entity.h"

class Obstacle : public Entity
{
private:
	bool destroyed;
	Texture2D textureObstacle;

public:
	Obstacle(
		Vector2 position, Vector2 velocity,
		int width, int height,
		Texture2D textureObstacle);
	~Obstacle();

	void Draw();

	void Movement();

	bool OutOfLimits();

	void SetDestroyed(bool setter);
	bool IsDestroyed();
};