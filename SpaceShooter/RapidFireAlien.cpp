#include "RapidFireAlien.hpp"

RapidFireAlien::RapidFireAlien(int x, int y, std::string sprite)
{
    location = Coordinate(x,y);
    width = 54;
    height = 59;
    hp = 2;
    speed = 1;
    shotSpeed = 1;
    shotWidth = 15;
    fireRate = 3;
    scoreValue = 4;
    this->spriteName = sprite;
    direction = 1;
}
