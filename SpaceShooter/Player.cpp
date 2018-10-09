#include "Player.hpp"
using namespace std;

Player::Player()
{
	this->size = 0;
	this->location = Coordinate(0, 0);
	this->speed = 1;
	this->shotSpeed = 1;
	this->shield = false;
}

Player::Player(int x, int y, int width, int height, bool shield, int shotSpeed, int speed, vector<Upgrade *> activePowerUps, std::string sprite)
{
	this->location = Coordinate(x, y);
	this->width = width;
	this->height = height;
	this->shield = shield;
	this->shotSpeed = shotSpeed;
	this->speed = speed;
	vector<Upgrade *> newUpgrades;
	this->spriteName = sprite;
	for (vector<Upgrade *>::iterator it = this->activePowerUps.begin(); it != this->activePowerUps.end(); ++it)
	{
		this->activePowerUps.erase(it);
		delete *it;
	}
	for (vector<Upgrade *>::iterator it = activePowerUps.begin(); it != activePowerUps.end(); ++it)
	{
		Upgrade *temp = *it;
		Upgrade temp2(*temp);
		this->activePowerUps.push_back(new Upgrade(temp2));
	}
}

Player::~Player()
{
	//nothing
}

Missile *Player::shoot()
{
	Missile *playerShot = new Missile(this->location.getX() + 21, this->location.getY() - 32, shotWidth, shotHeight, true, -1 * this->shotSpeed, "playerMissile"); //TODO make this appear at tip of players weapon rather than center
	return playerShot;
}

void Player::move(int dir)
{
	this->location.x = this->location.x + (dir * this->speed);
}

void Player::speedUp(int inc)
{
	speed += inc;
}

void Player::shotSpeedUp(int inc)
{
	shotSpeed += inc;
}
