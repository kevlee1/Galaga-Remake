#include "GameModel.hpp"

GameModel::GameModel()
{
	this->levelNum = 1;
	this->needsSave = false;
	this->isPaused = false;
	this->state = playing;
	score = 0;
	this->levels = list<Level *>();
	this->username = "";
	this->password = "";
}

GameModel::GameModel(list<Level *> levels)
{
	this->levelNum = 1;
	this->needsSave = false;
	this->state = playing;
	score = 0;
	for (list<Level *>::const_iterator it = this->levels.begin(); it != this->levels.end(); ++it)
	{
		delete *it;
	}
	for (list<Level *>::const_iterator it = levels.begin(); it != levels.end(); ++it)
	{
		Level *temp = *it;
		Level temp2(*temp);
		this->levels.push_back(new Level(temp2));
	}
}

GameModel::GameModel(int score, vector<int> playerLives, list<Level *> levels, string username, string password)
{
	this->levelNum = 1;
	this->needsSave = false;
	this->state = playing;
	this->score = score;
	this->level = *levels.front();
	this->playerLives = playerLives;
	for (list<Level *>::const_iterator it = this->levels.begin(); it != this->levels.end(); ++it)
	{
		delete *it;
	}
	for (list<Level *>::const_iterator it = levels.begin(); it != levels.end(); ++it)
	{
		Level *temp = *it;
		Level temp2(*temp);
		this->levels.push_back(new Level(temp2));
	}
	this->levels.pop_front();
	this->username = username;
	this->password = password;
}

GameModel::~GameModel()
{
	for (list<Level *>::const_iterator it = this->levels.begin(); it != this->levels.end(); ++it)
	{
		delete *it;
	}
}

void GameModel::nextLevel()
{
	if (levels.empty()) {
		this->state = won;
	}
	else {
		this->levelNum++;
		int i = level.getLives();
		this->level = *levels.front();
		this->level.setLives(i);
		this->levels.pop_front();
	}
}

void GameModel::updateScore()
{
}

void GameModel::playerMove(int dir)
{
	this->level.movePlayer(dir);
}

void GameModel::playerShoot()
{
	this->level.playerFired();
}

void GameModel::enemyShoot() {
	this->level.enemyFired();
}

void GameModel::enemyMoveLeft() {
    this->level.moveAllEnemiesLeft();
}

void GameModel::enemyMoveRight() {
    this->level.moveAllEnemiesRight();
}

void GameModel::run()
{
}

void GameModel::pause()
{
}

void GameModel::save()
{
	this->needsSave = true;
}

void GameModel::load(const int score, const int lives, const int levelNum)
{
	for (int i = 1; i < levelNum; ++i) {
		this->nextLevel();
	}
	this->level.setLives(lives);
	this->score = score;
}

void GameModel::tick()
{
	if (this->level.getState()== win) {
		this->nextLevel();
		this->save();
	}
	else if (this->level.getState() == lose) {
		this->state = lost;
	}
	else {
		this->level.tick();
		this->score += this->level.updateScore();
		this->level.flushScoreBuffer();
	}
}


vector<Blueprint> GameModel::getBlueprints()
{
	return this->level.getBlueprints();
}

int GameModel::getScore() const {
	return this->score;
}

int GameModel::getLives() const {
	return this->level.getLives();
}
