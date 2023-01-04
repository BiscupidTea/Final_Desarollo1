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

	void SetPosition(Vector2 position);
	Vector2 GetPosition();
	
	void setVelocityX(int velX);
	void setVelocityY(int velY);
	int getVelocityX();
	int getVelocityY();

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
};


