#include "Coordinate.hpp"

Coordinate::Coordinate()
{
	this->x = 0;
	this->y = 0;
}

Coordinate::Coordinate(int x, int y)
{
	this->x = x;
	this->y = y;
}

Coordinate::~Coordinate()
{
	//nothing
}

int Coordinate::getX() const
{
	return this->x;
}

int Coordinate::getY() const
{
	return this->y;
}

Coordinate &Coordinate::operator=(const Coordinate &other)
{
	this->x = other.getX();
	this->y = other.getY();

	return *this;
}
