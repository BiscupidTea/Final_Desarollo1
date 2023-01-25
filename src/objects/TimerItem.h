#pragma once
#include "Entity.h"
#include "raylib.h"
#include "raymath.h"

class TimerItem : public Entity
{
private:
	float timeAdd;

public:
	TimerItem(
		Vector2 position, Vector2 velocity, 
		int width, int height,
		float timeAdd);
	~TimerItem();

	void Draw();

	void UpdateItem();

	float GettimeAdd();
		
};

