#ifndef SALIEN_H
#define SALIEN_H

#include "Enemy.hpp"

// Stronger enemy meaning faster fire rate - 2
class StrongerAlien : public Enemy
{
public:
	StrongerAlien(int x, int y, std::string sprite);
};

#endif
