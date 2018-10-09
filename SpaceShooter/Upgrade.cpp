#include "Upgrade.hpp"
#include <iostream>

Upgrade::Upgrade()
{
	location = Coordinate(0, 0);
	size = 0;
	spawnTime = 0;
}

Upgrade::Upgrade(int x, int y, int width, int height, int speed, int spawnTime, UpgradeType type, std::string sprite)
{
	this->type = type;
	this->location = Coordinate(x, y);
	this->width = width;
	this->height = height;
	this->speed = speed;
	this->spawnTime = spawnTime;
	this->spriteName = sprite;
}

Upgrade::~Upgrade()
{
	//nothing
}

void Upgrade::upgradePlayer(Player *p)
{
	switch (type)
	{
	case shield:
		p->shield = true;
		break;
	case life:
		// handled in level
		break;
	case moveSpeed:
		p->speedUp(2);
		break;
	};
}

int Upgrade::getSpeed() const
{
	return speed;
}

void Upgrade::moveIncrement()
{

	location = Coordinate(location.x, location.y + speed);
}
