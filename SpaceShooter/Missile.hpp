#ifndef MISSILE_HPP
#define MISSILE_HPP

#include "Coordinate.hpp"
#include "Collidable.hpp"

class Missile : public Collidable
{
  public:
	Missile();
	Missile(int x, int y, int width, int height, bool isFriendly, int speed, std::string sprite);
	~Missile();

	// moves the missile
	void moveIncrement();
    // getter for the isFriendly field
	bool getFriendly();

  private:
	bool isFriendly;
	int speed;
};

#endif
