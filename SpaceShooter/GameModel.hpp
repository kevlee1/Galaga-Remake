#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP
#include "Player.hpp"
#include "Coordinate.hpp"
#include "Missile.hpp"
#include "Collidable.hpp"
#include "Upgrade.hpp"
#include "Level.hpp"
#include <vector>
#include <list>
#include <cstdint>
#include <string>

using namespace std;

// enum for the gamestate - there can be three - won, loss, and playing
enum GameState {
	won, lost, playing
};

// class for the model
class GameModel
{
private:
	bool isPaused;
	int score;
	Level level;
	vector<int> playerLives;
	list<Level *> levels;
	string username;
	string password;
	void nextLevel();
	void updateScore();


public:
	GameState state;
	bool needsSave;
	int levelNum;

	GameModel();
	GameModel(list<Level *> levels);
	GameModel(int score, vector<int> playerLives, list<Level *> levels, string username, string password);
	~GameModel();
    // moves the player | 1 = right, -1 = left
	void playerMove(int dir);
    // creates missiles for the player that shoot
	void playerShoot();
    // makes the enemies shoot
	void enemyShoot();
    // moves enemies left by changing their direction value
    void enemyMoveLeft();
    // moves enemies right by changing their direction value
    void enemyMoveRight();
    // runs the game
	void run();
    // pauses the game
	void pause();
    // saves the game
	void save();
    // loads a save for the game
	void load(const int score, const int lives, const int levelNum);
    // updates the tick and the gamestate
	void tick();
    // getter for the score
	int getScore() const;
    // getter for the lives
	int getLives() const;
    // getter for the blueprints
	vector<Blueprint> getBlueprints();
};
#endif
