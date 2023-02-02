#pragma once
#include "Entity.h"

#include "tools/Tools.h"
#include "tools/Timer.h"

class PowerUp :	public Entity
{
private:
	bool picked;

public:
	Timer* spawnItem;
	PowerUp(Vector2 position, Vector2 velocity, 
		int width, int height, float spawnTime);
	~PowerUp();

	void Draw();

	void UpdateItem();

	bool OutOfLimits();
	void ResetRandPosition();

	void SetPicked(bool setter);
	bool IsPicked();
};

