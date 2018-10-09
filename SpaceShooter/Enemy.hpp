#ifndef ENEMY_H
#define ENEMY_H

#include "Collidable.hpp"
#include "Missile.hpp"

// Represents a base enemy class that all enemies will inherit from
class Enemy : public Collidable
{
public:
  int speed;
  // virtual function that creates a missile from an enemy - needed for boss enemy
  virtual Missile *shoot() const;
  // reduces the enemies hp by the inputed damage
  void takeDamage(int dmg);
  // getter for the hp
  int getHP();
  // getter for which direction the enemy will move - 1 = right , -1 = left
  int direction;
  // change the direction value
  void changeDirection();
  // getter for the score 
  int getScoreValue();

protected:
  int hp;
  int shotSpeed;
  int shotHeight;
  int shotWidth;
  int fireRate;
  int scoreValue;

};

#endif
