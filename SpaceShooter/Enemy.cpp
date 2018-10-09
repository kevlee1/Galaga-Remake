#include "Enemy.hpp"
#include "Missile.hpp"

Missile *Enemy::shoot() const
{
    Missile *missile = new Missile(location.getX() + (this->getWidth()/2) - 8, location.getY() + (this->getHeight()/2), shotWidth, shotHeight, false, shotSpeed, "enemyMissile");
    return missile;
}

void Enemy::takeDamage(int dmg)
{
    if (hp - dmg <= 0)
    {
        hp = 0;
    }
    else
    {
        hp = hp - dmg;
    }
}

int Enemy::getHP()
{
    return hp;
}

int Enemy::getScoreValue() {
    return scoreValue;
}

void Enemy::changeDirection()
{
    direction = direction * -1;
}
