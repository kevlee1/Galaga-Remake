#include "Coordinate.hpp"
#include "Missile.hpp"
#include "Collidable.hpp"

#include <iostream>

Missile::Missile()
{
	this->location = Coordinate(0, 0);
	this->size = 0;
	this->isFriendly = true;
	this->speed = 0;
}

Missile::Missile(int x, int y, int width, int height, bool isFriendly, int speed, std::string sprite)
{
	this->location = Coordinate(x, y);
	this->width = width;
	this->height = height;
	this->isFriendly = isFriendly;
	this->speed = speed;
	this->spriteName = sprite;
}

Missile::~Missile()
{
	//nothing
}

void Missile::moveIncrement()
{

	this->location = Coordinate(this->location.x, this->location.y + this->speed);
}

bool Missile::getFriendly()
{
	return isFriendly;
}
