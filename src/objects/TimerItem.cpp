#include "TimerItem.h"

TimerItem::TimerItem(Vector2 position, Vector2 velocity, int width, int height, float timeAdd) : Entity(position, velocity, width, height)
{
	this->position = position;
	this->velocity = velocity;
	this->width = width;
	this->height = height;
	this->timeAdd = timeAdd;
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
	//position.y -= static_cast<float>(sin(position.x/10) * GetFrameTime() * velocity.x);

	if (position.x + width < 0)
	{
		position.x = static_cast<float>(GetScreenWidth());
	}
}

float TimerItem::GettimeAdd()
{
	return timeAdd;
}