#include "Level.hpp"
#include "Player.hpp"
#include "Upgrade.hpp"
#include "Missile.hpp"
#include "Enemy.hpp"
#include "BasicAlien.hpp"
#include <vector>
#include <time.h>
#include "StrongerAlien.hpp"
#include "RapidFireAlien.hpp"
#include "BossAlien.hpp"
using namespace std;

#include <iostream>

Level::Level()
{
	this->tickCounter = 0;
	this->scoreBuffer = 0;
	this->lives = 0;
	this->state = active;
}

Level::Level(int lives)
{
	this->tickCounter = 0;
	this->scoreBuffer = 0;
	this->lives = lives;
	this->state = active;
}

Level::Level(vector<Player *> players, vector<Enemy *> enemies, vector<Upgrade *> powerUps, vector<Missile *> missiles, int lives)
{
	for (vector<Player *>::iterator it = this->players.begin(); it != this->players.end(); ++it)
	{
		this->players.erase(it);
		delete *it;
	}
	for (vector<Player *>::const_iterator it = players.begin(); it != players.end(); ++it)
	{
		Player *temp = *it;
		Player temp2(*temp);
		this->players.push_back(new Player(temp2));
	}
	for (vector<Enemy *>::iterator it = this->enemies.begin(); it != this->enemies.end(); ++it)
	{
		this->enemies.erase(it);
		delete *it;
	}
	for (vector<Enemy *>::const_iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		Enemy *temp = *it;
		Enemy temp2(*temp);
		this->enemies.push_back(new Enemy(temp2));
	}
	for (vector<Upgrade *>::iterator it = this->powerUps.begin(); it != this->powerUps.end(); ++it)
	{
		this->powerUps.erase(it);
		delete *it;
	}

	for (vector<Upgrade *>::const_iterator it = powerUps.begin(); it != powerUps.end(); ++it)
	{
		Upgrade *temp = *it;
		Upgrade temp2(*temp);
		this->powerUps.push_back(new Upgrade(temp2));
	}

	for (vector<Missile *>::iterator it = this->missiles.begin(); it != this->missiles.end(); ++it)
	{
		this->missiles.erase(it);
		delete *it;
	}

	for (vector<Missile *>::const_iterator it = missiles.begin(); it != missiles.end(); ++it)
	{
		Missile temp = **it;
		Missile *temp2 = new Missile(temp);
		this->missiles.push_back(temp2);
	}
	tickCounter = 0;
	scoreBuffer = 0;
	this->lives = lives;
	this->state = active;
}

Level::~Level()
{
	// for (vector<Player *>::iterator it = this->players.begin(); it != players.end(); ++it)
	// {
	// 	delete *it;
	// }

	// for (vector<Enemy *>::iterator it = this->enemies.begin(); it != enemies.end(); ++it)
	// {
	// 	delete *it;
	// }

	// for (vector<Upgrade *>::iterator it = powerUps.begin(); it != powerUps.end(); ++it)
	// {
	// 	delete *it;
	// }

	// for (vector<Missile *>::iterator it = missiles.begin(); it != missiles.end(); ++it)
	// {
	// 	delete *it;
	// }
}

int Level::flushBuffer()
{
	return 0;
}

void Level::tick()
{
	tickCounter++;

	moveMissiles();
	moveEnemies();

	for (vector<Upgrade *>::iterator itr = powerUps.begin(); itr != powerUps.end(); ++itr)
	{
		if (tickCounter == (*itr)->spawnTime)
		{
			Upgrade *upgrade = *itr;
			switch (upgrade->type)
			{
			case shield:
				upgrade->spriteName = "powerupShield";
				break;
			case moveSpeed:
				upgrade->spriteName = "powerupSpeed";
				break;
			case life:
				upgrade->spriteName = "powerupLife";
				break;
			}
		}

		if (tickCounter > (*itr)->spawnTime)
		{
			(*itr)->moveIncrement();
		}
	}
	checkCollision();
	cleanUp();
	updateStatus();
}

void Level::cleanUp()
{
	vector<Enemy *>::iterator it = enemies.begin();
	while (it != enemies.end())
	{
		Enemy *enemy = *it;
		if (enemy->getHP() == 0)
		{
			scoreBuffer += enemy->getScoreValue();
			it = enemies.erase(it);
			delete enemy;
		}
		else
		{
			it++;
		}
	}
}

void Level::updateStatus()
{
	if (enemies.size() == 0)
	{
		state = win;
	}
	else if (lives == 0)
	{
		state = lose;
	}
}

void Level::missileFired(Missile *m)
{
	missiles.push_back(m);
}

void Level::playerFired()
{
	Missile *shotFired = players[0]->shoot();
	missileFired(shotFired);
}

void Level::enemyFired()
{

	int enemyID;
	if (enemies.size() == 0)
		return;
	if (enemies.size() == 1)
	{
		enemyID = 0;
	}
	else
	{
		enemyID = rand() % (enemies.size() - 1);
	}
	Missile *shotFired = enemies[enemyID]->shoot();
	missileFired(shotFired);
}

void Level::moveMissiles()
{
	for (vector<Missile *>::iterator it = missiles.begin(); it != missiles.end(); ++it)
	{
		(*it)->moveIncrement();
	}
}

Enemy *Level::getLeftMostEnemy()
{
	Enemy *leftMost = nullptr;
	for (vector<Enemy *>::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (leftMost == nullptr)
		{
			leftMost = (*it);
		}
		if (leftMost->getLocation().getX() > (*it)->getLocation().getX())
		{
			leftMost = (*it);
		}
	}
	return leftMost;
}

Enemy *Level::getRightMostEnemy()
{
	Enemy *rightMost = nullptr;
	for (vector<Enemy *>::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (rightMost == nullptr)
		{
			rightMost = (*it);
		}
		if (rightMost->getLocation().getX() < (*it)->getLocation().getX())
		{
			rightMost = (*it);
		}
	}
	return rightMost;
}

void Level::changeAllEnemyDirections()
{
	for (vector<Enemy *>::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		(*it)->changeDirection();
	}
}

void Level::moveEnemies()
{
	Enemy *leftMost = this->getLeftMostEnemy();
	Enemy *rightMost = this->getRightMostEnemy();
	Coordinate leftMostLocation = leftMost->getLocation();
	Coordinate rightMostLocation = rightMost->getLocation();
	int leftMostX = leftMostLocation.getX();
	int rightMostX = rightMostLocation.getX();

	int left = 0;
	int right = 1080 - (rightMost->getWidth());
	if (leftMostX == left)
	{
		this->changeAllEnemyDirections();
	}
	if (rightMostX == right)
	{
		this->changeAllEnemyDirections();
	}
	if (leftMost->direction == 1)
	{
		moveAllEnemiesLeft();
	}
	if (rightMost->direction == -1)
	{
		moveAllEnemiesRight();
	}
}

// Check all collisions
void Level::checkCollision()
{
	checkUpgrade();
	checkMissiles();
}

// Check if upgrades are colliding
void Level::checkUpgrade()
{
	vector<Upgrade *>::iterator it = powerUps.begin();
	while (it != powerUps.end())
	{
		bool deleted = false;
		Upgrade *upgrade = *it;
		for (vector<Player *>::iterator it2 = players.begin(); it2 != players.end(); ++it2)
		{
			Player *player = *it2;
			if (upgrade->isColliding(*player))
			{
				if (upgrade->type == life)
				{
					lives++;
				}
				upgrade->upgradePlayer(player);
				it = powerUps.erase(it);
				delete upgrade;
				deleted = true;
				break;
			}
		}

		if (!deleted)
		{
			it++;
		}
	}
}

// Check if missiles are colliding
void Level::checkMissiles()
{
	vector<Missile *>::iterator it = missiles.begin();
	while (it != missiles.end())
	{
		bool deleted = false;
		Missile *missile = *it;
		if (missile->getFriendly())
		{
			for (vector<Enemy *>::iterator it2 = enemies.begin(); it2 != enemies.end(); ++it2)
			{
				Enemy *enemy = *it2;
				if (missile->isColliding(*enemy))
				{
					enemy->takeDamage(1);
					it = this->missiles.erase(it);
					delete missile;
					deleted = true;
					break;
				}
			}
		}
		else
		{
			for (vector<Player *>::iterator it2 = players.begin(); it2 != players.end(); ++it2)
			{
				Player *player = *it2;
				if (missile->isColliding(*player))
				{
					if (player->shield)
					{
						player->shield = false;
					}
					else
					{
						if (lives > 0)
							lives--;
					}

					it = missiles.erase(it);
					delete missile;
					deleted = true;
					break;
				}
			}
		}

		if (!deleted)
		{
			it++;
		}
	}
}

// int dir = 1 -> right
// int dir = -1 -> left
void Level::movePlayer(int dir)
{
	int playerX = players[0]->getLocation().getX();
	int right = 1080 - players[0]->getWidth();
	int left = 0;
	if (playerX > right && dir == 1)
	{
		return;
	}
	if (playerX < left && dir == -1)
	{
		return;
	}
	else
	{
		players[0]->move(dir);
	}
}

vector<Blueprint> Level::getBlueprints()
{
	vector<Blueprint> bps;

	for (vector<Player *>::const_iterator it = players.begin(); it != players.end(); ++it)
	{
		bps.push_back((*it)->generateBlueprint());
	}

	for (vector<Enemy *>::const_iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		bps.push_back((*it)->generateBlueprint());
	}

	for (vector<Upgrade *>::const_iterator it = powerUps.begin(); it != powerUps.end(); ++it)
	{
		bps.push_back((*it)->generateBlueprint());
	}

	for (vector<Missile *>::const_iterator it = missiles.begin(); it != missiles.end(); ++it)
	{
		bps.push_back((*it)->generateBlueprint());
	}

	return bps;
}

void Level::moveAllEnemiesLeft()
{
	int moveInt;
	for (vector<Enemy *>::iterator it = this->enemies.begin(); it != enemies.end(); ++it)
	{
		moveInt = (*it)->speed;
		moveInt = moveInt * -1;
		(*it)->move(moveInt, 0);
	}
}

void Level::moveAllEnemiesRight()
{
	int moveInt;
	for (vector<Enemy *>::iterator it = this->enemies.begin(); it != enemies.end(); ++it)
	{
		moveInt = (*it)->speed;
		(*it)->move(moveInt, 0);
	}
}

int Level::moveTotalInt(int wLength, int eSize, int eCount, int eApart)
{
	int distanceMove;
	int total;

	int loEnemy = (eSize * eCount) + (eApart * (eCount - 1));

	total = wLength - loEnemy;

	if (total % 2 == 1)
	{
		total = total - 1;
		distanceMove = total / 2;
	}
	else
	{
		distanceMove = total / 2;
	}
	return distanceMove;
}

LevelState Level::getState() const
{
	return state;
}

void Level::firstLevel()
{
	tickCounter = 0;
	scoreBuffer = 0;

	// enemy size = 54
	// player size = 58
	// window length = 1080
	// window height = 800

	powerUps = vector<Upgrade *>();

	Player *player = new Player(511, 742, 58, 64, false, 1, 10, powerUps, "player");
	Enemy *bEnemy1 = new BasicAlien(382, 9, "enemy1");
	Enemy *bEnemy6 = new BasicAlien(382, 72, "enemy1");
	Enemy *bEnemy2 = new BasicAlien(445, 9, "enemy1");
	Enemy *bEnemy7 = new BasicAlien(445, 72, "enemy1");
	Enemy *bEnemy3 = new BasicAlien(508, 9, "enemy1");
	Enemy *bEnemy8 = new BasicAlien(508, 72, "enemy1");
	Enemy *bEnemy4 = new BasicAlien(571, 9, "enemy1");
	Enemy *bEnemy9 = new BasicAlien(571, 72, "enemy1");
	Enemy *bEnemy5 = new BasicAlien(634, 9, "enemy1");
	Enemy *bEnemy10 = new BasicAlien(634, 72, "enemy1");
	Upgrade *shield1 = new Upgrade(50, 50, 28, 28, 1, 300, moveSpeed, "");
	Upgrade *shield2 = new Upgrade(458, 100, 28, 28, 1, 10000, life, "");
	Upgrade *shield3 = new Upgrade(521, 100, 28, 28, 1, 15000, life, "");
	Upgrade *shield4 = new Upgrade(584, 100, 28, 28, 1, 20000, life, "");
	Upgrade *shield5 = new Upgrade(647, 100, 28, 28, 1, 25000, life, "");

	players.push_back(player);
	enemies.push_back(bEnemy1);
	enemies.push_back(bEnemy2);
	enemies.push_back(bEnemy3);
	enemies.push_back(bEnemy4);
	enemies.push_back(bEnemy5);
	enemies.push_back(bEnemy6);
	enemies.push_back(bEnemy7);
	enemies.push_back(bEnemy8);
	enemies.push_back(bEnemy9);
	enemies.push_back(bEnemy10);
	powerUps.push_back(shield1);
	powerUps.push_back(shield2);
	powerUps.push_back(shield3);
	powerUps.push_back(shield4);
	powerUps.push_back(shield5);
}

void Level::secondLevel()
{

	powerUps = vector<Upgrade *>();

	Player *player = new Player(511, 742, 58, 64, false, 1, 10, powerUps, "player");
	Enemy *bEnemy1 = new BasicAlien(382, 9, "enemy1");
	Enemy *sEnemy6 = new StrongerAlien(382, 72, "enemy2");
	Enemy *bEnemy2 = new BasicAlien(445, 9, "enemy1");
	Enemy *sEnemy7 = new StrongerAlien(445, 72, "enemy2");
	Enemy *bEnemy3 = new BasicAlien(508, 9, "enemy1");
	Enemy *sEnemy8 = new StrongerAlien(508, 72, "enemy2");
	Enemy *bEnemy4 = new BasicAlien(571, 9, "enemy1");
	Enemy *sEnemy9 = new StrongerAlien(571, 72, "enemy2");
	Enemy *bEnemy5 = new BasicAlien(634, 9, "enemy1");
	Enemy *sEnemy10 = new StrongerAlien(634, 72, "enemy2");
	Upgrade *shield1 = new Upgrade(395, 50, 28, 28, 1, 5000, moveSpeed, "");
	Upgrade *shield2 = new Upgrade(458, 100, 28, 28, 1, 10000, shield, "");
	Upgrade *shield3 = new Upgrade(521, 100, 28, 28, 1, 15000, life, "");
	Upgrade *shield4 = new Upgrade(584, 100, 28, 28, 1, 20000, moveSpeed, "");
	Upgrade *shield5 = new Upgrade(647, 100, 28, 28, 1, 25000, life, "");

	players.push_back(player);
	enemies.push_back(bEnemy1);
	enemies.push_back(sEnemy6);
	enemies.push_back(bEnemy2);
	enemies.push_back(sEnemy7);
	enemies.push_back(bEnemy3);
	enemies.push_back(sEnemy8);
	enemies.push_back(bEnemy4);
	enemies.push_back(sEnemy9);
	enemies.push_back(bEnemy5);
	enemies.push_back(sEnemy10);
	powerUps.push_back(shield1);
	powerUps.push_back(shield2);
	powerUps.push_back(shield3);
	powerUps.push_back(shield4);
	powerUps.push_back(shield5);
}

void Level::thirdLevel()
{

	powerUps = vector<Upgrade *>();

	Player *player = new Player(511, 742, 58, 64, false, 1, 10, powerUps, "player");
	Enemy *sEnemy1 = new StrongerAlien(382, 9, "enemy2");
	Enemy *sEnemy6 = new StrongerAlien(382, 72, "enemy2");
	Enemy *sEnemy2 = new StrongerAlien(445, 9, "enemy2");
	Enemy *sEnemy7 = new StrongerAlien(445, 72, "enemy2");
	Enemy *sEnemy3 = new StrongerAlien(508, 9, "enemy2");
	Enemy *sEnemy8 = new StrongerAlien(508, 72, "enemy2");
	Enemy *sEnemy4 = new StrongerAlien(571, 9, "enemy2");
	Enemy *sEnemy9 = new StrongerAlien(571, 72, "enemy2");
	Enemy *sEnemy5 = new StrongerAlien(634, 9, "enemy2");
	Enemy *sEnemy10 = new StrongerAlien(634, 72, "enemy2");
	Upgrade *shield1 = new Upgrade(395, 50, 28, 28, 1, 5000, shield, "");
	Upgrade *shield2 = new Upgrade(458, 100, 28, 28, 1, 10000, life, "");
	Upgrade *shield3 = new Upgrade(521, 100, 28, 28, 1, 15000, moveSpeed, "");
	Upgrade *shield4 = new Upgrade(584, 100, 28, 28, 1, 20000, moveSpeed, "");
	Upgrade *shield5 = new Upgrade(647, 100, 28, 28, 1, 25000, moveSpeed, "");

	players.push_back(player);
	enemies.push_back(sEnemy1);
	enemies.push_back(sEnemy6);
	enemies.push_back(sEnemy2);
	enemies.push_back(sEnemy7);
	enemies.push_back(sEnemy3);
	enemies.push_back(sEnemy8);
	enemies.push_back(sEnemy4);
	enemies.push_back(sEnemy9);
	enemies.push_back(sEnemy5);
	enemies.push_back(sEnemy10);
	powerUps.push_back(shield1);
	powerUps.push_back(shield2);
	powerUps.push_back(shield3);
	powerUps.push_back(shield4);
	powerUps.push_back(shield5);
}

void Level::fourthLevel()
{
	powerUps = vector<Upgrade *>();

	Player *player = new Player(511, 742, 58, 64, false, 1, 10, powerUps, "player");
	Enemy *rpEnemy1 = new RapidFireAlien(450, 9, "enemy3");
	Enemy *rpEnemy2 = new RapidFireAlien(513, 9, "enemy3");
	Enemy *rpEnemy3 = new RapidFireAlien(576, 9, "enemy3");
	Enemy *sEnemy1 = new StrongerAlien(414, 60, "enemy2");
	Enemy *sEnemy2 = new StrongerAlien(477, 60, "enemy2");
	Enemy *sEnemy3 = new StrongerAlien(549, 60, "enemy2");
	Enemy *sEnemy4 = new StrongerAlien(612, 60, "enemy2");
	Enemy *bEnemy1 = new BasicAlien(378, 111, "enemy1");
	Enemy *bEnemy2 = new BasicAlien(450, 111, "enemy1");
	Enemy *bEnemy3 = new BasicAlien(513, 111, "enemy1");
	Enemy *bEnemy4 = new BasicAlien(576, 111, "enemy1");
	Enemy *bEnemy5 = new BasicAlien(639, 111, "enemy1");
	Upgrade *shield1 = new Upgrade(395, 50, 28, 28, 1, 5000, moveSpeed, "");
	Upgrade *shield2 = new Upgrade(458, 100, 28, 28, 1, 10000, moveSpeed, "");
	Upgrade *shield3 = new Upgrade(521, 100, 28, 28, 1, 15000, moveSpeed, "");
	Upgrade *shield4 = new Upgrade(584, 100, 28, 28, 1, 20000, shield, "");
	Upgrade *shield5 = new Upgrade(647, 100, 28, 28, 1, 25000, life, "");

	players.push_back(player);
	enemies.push_back(bEnemy1);
	enemies.push_back(sEnemy1);
	enemies.push_back(rpEnemy1);
	enemies.push_back(bEnemy2);
	enemies.push_back(sEnemy2);
	enemies.push_back(bEnemy3);
	enemies.push_back(rpEnemy2);
	enemies.push_back(sEnemy3);
	enemies.push_back(bEnemy4);
	enemies.push_back(rpEnemy3);
	enemies.push_back(sEnemy4);
	enemies.push_back(bEnemy5);
	powerUps.push_back(shield1);
	powerUps.push_back(shield2);
	powerUps.push_back(shield3);
	powerUps.push_back(shield4);
	powerUps.push_back(shield5);
}

void Level::bossLevel()
{

	powerUps = vector<Upgrade *>();

	Player *player = new Player(511, 742, 58, 64, false, 1, 10, powerUps, "player");

	Enemy *bEnemy1 = new BasicAlien(96, 77, "enemy1");
	Enemy *bEnemy2 = new BasicAlien(216, 77, "enemy1");
	Enemy *bEnemy3 = new BasicAlien(810, 77, "enemy1");
	Enemy *bEnemy4 = new BasicAlien(930, 77, "enemy1");

	Enemy *sEnemy1 = new StrongerAlien(336, 170, "enemy2");
	Enemy *sEnemy2 = new StrongerAlien(513, 170, "enemy2");
	Enemy *sEnemy3 = new StrongerAlien(690, 170, "enemy2");

	Enemy *rpEnemy1 = new RapidFireAlien(216, 9, "enemy3");
	Enemy *rpEnemy2 = new RapidFireAlien(810, 9, "enemy3");

	Enemy *boss = new BossAlien(486, 9, "boss1");

	players.push_back(player);
	enemies.push_back(boss);
	enemies.push_back(bEnemy1);
	enemies.push_back(bEnemy2);
	enemies.push_back(bEnemy3);
	enemies.push_back(bEnemy4);
	enemies.push_back(sEnemy1);
	enemies.push_back(sEnemy2);
	enemies.push_back(sEnemy3);
	enemies.push_back(rpEnemy1);
	enemies.push_back(rpEnemy2);
}

int Level::getLives() const
{
	return this->lives;
}

void Level::setLives(int num)
{
	this->lives = num;
}

int Level::updateScore()
{
	return this->scoreBuffer;
}

void Level::flushScoreBuffer()
{
	this->scoreBuffer = 0;
}
