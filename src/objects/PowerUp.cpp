#include "PowerUp.h"

PowerUp::PowerUp(Vector2 position, Vector2 velocity, int width, int height, float spawnTime) : Entity(position, velocity, width, height)
{
	this->position = position;
	this->velocity = velocity;
	this->width = width;
	this->height = height;
	this->picked = false;

	this->spawnItem = new Timer(spawnTime);
}

PowerUp::~PowerUp()
{

}

void PowerUp::Draw()
{
	DrawRectangle(static_cast<int>(GetX()), static_cast<int>(GetY()), width, height, SKYBLUE);
}

void PowerUp::UpdateItem()
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

void PowerUp::ResetRandPosition()
{
	float midPlayableScreen = GetPercentageScreenHeight(42.5);
	position.x = static_cast<float>(GetScreenWidth());

	if (GetRandomValue(1,2) == 1)
	{
		position.y = midPlayableScreen - (midPlayableScreen / 2);
	}
	else
	{
		position.y = midPlayableScreen + (midPlayableScreen / 2);
	}

	spawnItem->ResetTime();
}