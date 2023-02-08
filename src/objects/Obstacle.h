#pragma once
#include <iostream>
#include "tools/tools.h"
#include "tools/Timer.h"

#include "Entity.h"

using namespace std;

class Obstacle : public Entity
{
private:
	bool destroyed;

	Timer* changeFrame;
	Timer* changeFrameDeath;
	Texture2D textureObstacle;
	Texture2D textureObstacleDestroyed;
	int actualFrame;

public:
	Obstacle(
		Vector2 position, Vector2 velocity,
		int width, int height,
		Texture2D textureObstacle,
		Texture2D textureObstacleDestroyed
	);
	~Obstacle();

	void Draw();

	void UpdateDraw();

	void Movement();

	bool OutOfLimits();

	void SetDestroyed(bool setter);
	bool IsDestroyed();

	void setDeathAnimation();
};