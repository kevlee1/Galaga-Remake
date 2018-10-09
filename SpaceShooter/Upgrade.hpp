#ifndef UPGRADE_HPP
#define UPGRADE_HPP

#include "Coordinate.hpp"
#include "Collidable.hpp"
#include "Player.hpp"

class Player;

enum UpgradeType
{
	shield,
	life,
	moveSpeed,
};

class Upgrade : public Collidable
{
  public:
	Upgrade();
	Upgrade(int x, int y, int width, int height, int speed, int spawnTime, UpgradeType type, std::string sprite);
	// Upgrade(const Upgrade &other);
	~Upgrade();

	// moves the upgrade
	void moveIncrement();

	// upgrades the player
	void upgradePlayer(Player *p);
	UpgradeType type;
	int spawnTime;
	int getSpeed() const;

  private:
	int speed;
};

#endif
