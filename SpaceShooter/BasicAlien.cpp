#include "BasicAlien.hpp"

BasicAlien::BasicAlien(int x, int y, std::string sprite)
{
    location = Coordinate(x, y);
    width = 54;
    height = 42;
    hp = 1;
    speed = 1;
    shotSpeed = 1;
    shotWidth = 15;
    shotHeight = 27;
    fireRate = 1;
    scoreValue = 1;
    this->spriteName = sprite;
    direction = 1;
}
