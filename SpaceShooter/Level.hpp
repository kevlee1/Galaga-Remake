#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include "Player.hpp"
#include "Upgrade.hpp"
#include "Missile.hpp"
#include "Enemy.hpp"
#include "Blueprint.hpp"
using namespace std;

// enum for the state of the level
enum LevelState
{
	win,
	lose,
	active
};

// class that represents a level in the game
class Level
{
private:
	vector<Player *> players;
	vector<Enemy *> enemies;
	vector<Upgrade *> powerUps;
	vector<Missile *> missiles;
	int tickCounter;
	LevelState state;
	int scoreBuffer;
	int lives;

    // cleans up all pointers and objects that are no longer needed - gets rid of missiles that are off screen
	void cleanUp();

	// update the status of the level state
	void updateStatus();

	// adds the fired missile into the vector of missiles
	void missileFired(Missile *m);

	// checks collision from objects within the level
	void checkCollision();

	// helper for checkCollision(). see if it is collision with an upgrade and updates the player accordingly
	void checkUpgrade();

	// helper for checkCollision(). see if it is a collision with a missile and updates the level accordingly
	void checkMissiles();

    // moves the missiles forward
	void moveMissiles();
    // moves the enemies
	void moveEnemies();
    
    // changes the direction value for all enemies in the vector
    void changeAllEnemyDirections();
    
    // finds the left most enemy in the vector
    Enemy *getLeftMostEnemy();
    // finds the right most enemy in the vector
    Enemy *getRightMostEnemy();

public:
	Level();
	Level(int lives);
	Level(vector<Player *> players, vector<Enemy *> enemies, vector<Upgrade *> powerUps, vector<Missile *> missiles, int lives);
	~Level();
    // flushes the buffer - makes it 0
	int flushBuffer();
    // updates the tick counter | moves the missiles | moves the enemies | handles powerup spawns | checks for collisions | cleans up unnecessary objects | and updates the status
	void tick();
    // generates the blueprints
	vector<Blueprint> getBlueprints();
    // moves the player - stops them from going out of bounds
	void movePlayer(int dir);
	// helper for missileFired().  fires the missiles with properties derived from the player
	void playerFired();
	// helper for missileFired().  fires the missiles with properties derived from the enemy
	void enemyFired();
	// moves enemies the correct amount to the left
	void moveAllEnemiesLeft();
	// moves enemies the correct amount to the right
	void moveAllEnemiesRight();
	//get lives
	int getLives() const;
	//set lives
	void setLives(const int num);
	//sets the score to however much needed after enemies killed
	int updateScore();
    // flushes the scoreBuffer to 0
	void flushScoreBuffer();

	// gets max distance enemy can move either left or right
	// wLength - length of window
	// eSize - size of enemy
	// eCount - number of enemies in a row
	// eApart - distance enemies are apart
	int moveTotalInt(int wLength, int eSize, int eCount, int eApart);

	// sets the first level up
	void firstLevel();
	void secondLevel();
	void thirdLevel();
	void fourthLevel();
	void bossLevel();
    // returns the state
	LevelState getState() const;
};
#endif
