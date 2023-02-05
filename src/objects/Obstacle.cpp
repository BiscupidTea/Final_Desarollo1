#include "Obstacle.h"

Obstacle::Obstacle(Vector2 position, Vector2 velocity, int width, int height, Texture2D textureObstacle) : Entity(position, velocity, width, height)
{
	this->position = position;
	this->velocity = velocity;

	this->textureObstacle = textureObstacle;
	this->width = textureObstacle.width;
	this->height = textureObstacle.height;

	this->destroyed = false;

}

Obstacle::~Obstacle()
{

}

void Obstacle::Draw()
{
	DrawRectangle(static_cast<int>(GetX()), static_cast<int>(GetY()), GetWidth(), GetHeight(), RED);
	DrawTexturePro(textureObstacle,
		{ 0, 0, 64, 64 },
		{ position.x,position.y, 64, 64 },
		{ 0,	0, },
		0, WHITE);
}

void Obstacle::Movement()
{
	position.x -= velocity.x * GetFrameTime();
}

bool Obstacle::OutOfLimits()
{
	if (GetX() + width < 0)
	{
		return true;
	}

	return false;
}

void Obstacle::SetDestroyed(bool setter)
{
	destroyed = setter;
}

bool Obstacle::IsDestroyed()
{
	return destroyed;
}