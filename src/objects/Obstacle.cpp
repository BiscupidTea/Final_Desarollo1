#include "Obstacle.h"

Obstacle::Obstacle(Vector2 position, Vector2 velocity, int width, int height) : Entity(position, velocity, width, height)
{
	this->position = position;
	this->velocity = velocity;
	this->width = width;
	this->height = height;
}

Obstacle::~Obstacle()
{

}

void Obstacle::Draw()
{
	DrawRectangle(static_cast<int>(GetX()), static_cast<int>(GetY()), GetWidth(), GetHeight(), RED);
}

void Obstacle::Movement()
{
	position.x -= velocity.x * GetFrameTime();
}

bool Obstacle::OutOfLimits()
{
	if (GetX() < 0)
	{
		return true;
	}

	return false;
}