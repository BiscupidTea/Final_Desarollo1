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
	DrawRectangle(position.x, position.y, width, height, RED);
}

void TimerItem::UpdateItem()
{
	position.x -= velocity.x * GetFrameTime();
	position.y -= sin(position.x/10) * GetFrameTime() * velocity.x;
}

float TimerItem::GettimeAdd()
{
	return timeAdd;
}