#ifndef BossAlien_H
#define BossAlien_H

#include "Enemy.hpp"

// boss alien with 20 hp - 10 score - and 2 shotSpeed - has a wider missile hitbox and sprite
class BossAlien : public Enemy
{
public:
    BossAlien(int x, int y, std::string sprite);
    // virtual method that shoots the different sprite necessary for the boss
    Missile *shoot() const;
};

#endif

