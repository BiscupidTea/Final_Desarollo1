#pragma once
#include "raylib.h"

class Entity
{
protected:
	Vector2 position;
	Vector2 velocity;
	int width;
	int height;

public:
	Entity(Vector2 position, Vector2 velocity, int width, int height);
	virtual ~Entity();

	virtual void Draw() = 0;

	void SetPosition(Vector2 newPosition);
	Vector2 GetPosition();
	
	void setVelocityX(float velX);
	void setVelocityY(float velY);
	float getVelocityX();
	float getVelocityY();

	float GetX();
	float GetY();
	int GetWidth();
	int GetHeight();
};


