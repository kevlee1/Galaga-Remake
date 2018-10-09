#include "Collidable.hpp"
#include <string>

Collidable::Collidable()
{
    this->size = 0;
    this->location = Coordinate(0, 0);
}

Collidable::~Collidable()
{
    //nothing
}

Collidable::Collidable(int x, int y, int size)
{
    this->size = size;
    this->location = Coordinate(x, y);
}

Collidable::Collidable(int x, int y, int width, int height)
{
    this->width = width;
    this->height = height;
    this->location = Coordinate(x, y);
}

bool Collidable::isColliding(const Collidable &c) const
{
    const Coordinate &coords = c.getLocation();
    int x1 = location.getX();
    int x2 = coords.getX();
    int y1 = location.getY();
    int y2 = coords.getY();
    int height2 = c.getHeight();
    int width2 = c.getWidth();

    return x1 < x2 + width2 && x1 + width > x2 && y1 < y2 + height2 && y1 + height > y2;
}

void Collidable::move(int x, int y)
{
    location = Coordinate(location.getX() + x, location.getY() + y);
}

const Coordinate &Collidable::getLocation() const
{
    return location;
}

int Collidable::getSize() const
{
    return size;
}

int Collidable::getWidth() const
{
    return width;
}

int Collidable::getHeight() const
{
    return height;
}

Blueprint Collidable::generateBlueprint() const
{
    Blueprint bp = {location, spriteName};
    return bp;
}
