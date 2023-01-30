#pragma once
#include "Entity.h"
#include "raylib.h"
#include "raymath.h"

#include "tools/Tools.h"

class TimerItem : public Entity
{
private:
	float timeAdd;
	float initPosition;
	float minSpace;
	float maxSpace;

	bool goingUp;

public:
	TimerItem(
		Vector2 position, Vector2 velocity, 
		int width, int height,
		float timeAdd, float initPosition);
	~TimerItem();

	void Draw();

	void UpdateItem();

	float GettimeAdd();
		
	void ResetRandPosition();
};

