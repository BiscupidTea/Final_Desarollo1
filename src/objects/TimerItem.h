#pragma once
#include "Entity.h"
#include "raylib.h"
#include "raymath.h"

#include "tools/Tools.h"
#include "tools/Timer.h"

class TimerItem : public Entity
{
private:
	float timeAdd;
	float timeToSpawn;
	float initPosition;
	float minSpace;
	float maxSpace;

	bool goingUp;

public:
	Timer* holdTimer;

	TimerItem(
		Vector2 position, Vector2 velocity, 
		int width, int height,
		float timeAdd, float initPosition, float timeToSpawn);
	~TimerItem();

	void Draw();

	void UpdateItem();

	float GettimeAdd();
		
	void ResetRandPosition();

	float GetTimeToSpawn();
};

