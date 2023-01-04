#include "Entity.h"

Entity::Entity(Vector2 position, int width, int height)
{
	this->position = position;
	this->width = width;
	this->height = height;
}

Entity::~Entity()
{

}

void Entity::SetPosition(Vector2 position)
{
	this->position = position;
}

Vector2 Entity::GetPosition()
{
	return position;
}

int Entity::GetX()
{
	return position.x;
}

int Entity::GetY()
{
	return position.y;
}

int Entity::GetWidth()
{
	return this->width;
}

int Entity::GetHeight()
{
	return this->height;
}
