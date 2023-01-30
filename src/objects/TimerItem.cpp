#include "TimerItem.h"

TimerItem::TimerItem(Vector2 position, Vector2 velocity, int width, int height, float timeAdd, float positionA, float positionB) : Entity(position, velocity, width, height)
{
	this->position = position;
	this->velocity = velocity;
	this->width = width;
	this->height = height;
	this->timeAdd = timeAdd;
	this->positionA = positionA;
	this->positionB = positionB;

	this->maxSpace = 0;
	this->minSpace = 0;

	this->goingUp = true;
}

TimerItem::~TimerItem()
{

}

void TimerItem::Draw()
{
	DrawRectangle(
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		width, height, YELLOW);
}

void TimerItem::UpdateItem()
{
	position.x -= velocity.x * GetFrameTime();

	if (goingUp)
	{
		position.y -= velocity.y * GetFrameTime();
	}
	else
	{
		position.y += velocity.y * GetFrameTime();
	}

	if (position.y < minSpace && goingUp)
	{
		goingUp = false;
	}
	else if (position.y + height > maxSpace && !goingUp)
	{
		goingUp = true;
	}

	if (position.x + width < 0)
	{
		ResetRandPosition();
	}
}

float TimerItem::GettimeAdd()
{
	return timeAdd;
}

void TimerItem::ResetRandPosition()
{
	float midPlayableScreen = GetPercentageScreenHeight(42.5);
	float maxPLayableScreen = GetPercentageScreenHeight(85);

	if (GetRandomValue(1, 2) == 1)
	{
		position.y = positionA;
		minSpace = 0;
		maxSpace = midPlayableScreen;
	}
	else
	{
		position.y = positionB;
		minSpace = midPlayableScreen;
		maxSpace = maxPLayableScreen;
	}

	position.x = static_cast<float>(GetScreenWidth());
}