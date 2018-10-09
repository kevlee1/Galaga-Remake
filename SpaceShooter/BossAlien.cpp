#include "BossAlien.hpp"

BossAlien::BossAlien(int x, int y, std::string sprite)
{
    location = Coordinate(x,y);
    width = 108;
    height = 84;
    hp = 20;
    speed = 1;
    shotSpeed = 1;
    shotWidth = 25;
    shotHeight = 27;
    fireRate = 2;
    scoreValue = 10;
    this->spriteName = sprite;
    direction = 1;
}

Missile *BossAlien::shoot() const
{
    Missile *missile = new Missile(location.getX(), location.getY(), shotWidth, shotHeight,false, shotSpeed, "bossMissile");
    return missile;
}
