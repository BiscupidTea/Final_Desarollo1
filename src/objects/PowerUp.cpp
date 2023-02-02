#include "PowerUp.h"

PowerUp::PowerUp(Vector2 position, Vector2 velocity, int width, int height) : Entity(position, velocity, width, height)
{
	this->position = position;
	this->velocity = velocity;
	this->width = width;
	this->height = height;
	this->picked = false;

	this->spawnItem = new Timer(30);
}

PowerUp::~PowerUp()
{

}

void PowerUp::Draw()
{
	DrawRectangle(static_cast<int>(GetX()), static_cast<int>(GetY()), width, height, SKYBLUE);
}

void PowerUp::Movement()
{
	position.x -= velocity.x * GetFrameTime();
}

bool PowerUp::OutOfLimits()
{
	if (GetX() + width < 0)
	{
		return true;
	}

	return false;
}

void PowerUp::SetPicked(bool setter)
{
	picked = setter;
}

bool PowerUp::IsPicked()
{
	return picked;
}