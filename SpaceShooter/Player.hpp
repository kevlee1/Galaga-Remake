#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Coordinate.hpp"
#include "Missile.hpp"
#include "Collidable.hpp"
#include "Upgrade.hpp"
#include <vector>
using namespace std;

class Upgrade;

// class for player
class Player : public Collidable
{
  private:
	int shotSpeed;

	// temporarily here
	int shotWidth = 15;
	int shotHeight = 28;
	int speed;
	vector<Upgrade *> activePowerUps;

  public:
	bool shield;

	Player();
	Player(int x, int y, int width, int height, bool shield, int shotSpeed, int speed, vector<Upgrade *> activePowerUps, std::string sprite);
    // moves the player
	void move(int dir);
	~Player();

	// shoots a missile
	Missile *shoot();
    // changes the speed by the given int
	void speedUp(int);
    // changes the shotSpeed by the given int
	void shotSpeedUp(int);
};
#endif
