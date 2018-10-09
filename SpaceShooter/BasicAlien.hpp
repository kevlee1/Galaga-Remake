#ifndef BALIEN_H
#define BALIEN_H

#include "Enemy.hpp"

// The most basic enemy - 1 hp - 1 fireRate - worth 1 point
class BasicAlien : public Enemy
{
public:
    BasicAlien(int x, int y, std::string sprite);
};

#endif
