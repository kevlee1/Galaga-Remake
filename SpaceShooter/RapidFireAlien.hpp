#ifndef RFALIEN_H
#define RFALIEN_H

#include "Enemy.hpp"

// class for rapid fire alien - hp 2, shotRate 2, score 4
class RapidFireAlien : public Enemy
{
public:
    RapidFireAlien(int x, int y, std::string sprite);
};

#endif
