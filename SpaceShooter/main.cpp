
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <cstdint>
#include <string>
#include <sstream>
#include <time.h>
#include <iostream>
#include "GameModel.hpp"
#include "View.hpp"
#include "Api.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 940;
const float PLAYER_FIRE_RATE = 1;
const int FRAME_SPEED_PLAYER = 25;
const int STARTING_LIVES = 3;
int FRAME_SPEED_ENEMY = 1000;

int main(int argc, char *args[])
{
	srand(time(NULL)); // dont delete this :), seeds randomization for enemy fire

	//preload all levels
	Level *testLevel2 = new Level(STARTING_LIVES);
	testLevel2->firstLevel();
	Level *testLevelEmpty = new Level(STARTING_LIVES);
	testLevelEmpty->secondLevel();
	Level *testLevel3 = new Level(STARTING_LIVES);
	testLevel3->thirdLevel();
	Level *testLevel4 = new Level(STARTING_LIVES);
	testLevel4->fourthLevel();
	Level *testLevelBoss = new Level(STARTING_LIVES);
	testLevelBoss->bossLevel();

	vector<int> playerLives = vector<int>();
	playerLives.push_back(3);
	list<Level *> levels = list<Level *>();
	levels.push_back(testLevel2);
	levels.push_back(testLevelEmpty);
	levels.push_back(testLevel3);
	levels.push_back(testLevel4);
	levels.push_back(testLevelBoss);

	GameModel game = GameModel(0, playerLives, levels, "", "");
	//initialize view
	View gameView = View(SCREEN_WIDTH, SCREEN_HEIGHT);
	gameView.init();


	//flags and game-global data
	bool quit = false;
	bool paused = false;
	uint32_t player1ShotTimer = 0;
	uint32_t player1MoveTimer = 0;
	uint32_t enemyShootTimer = 0;
	uint32_t enemyMoveTimer = 0;
	int move = 0;
	SDL_Event e;
	gameView.playMusic();
	SDL_StartTextInput();
	std::string inputText = "";
	bool loggedIn = false;
	bool userNameScreen = true;
	bool pwScreen = false;
	bool menuScreen = false;
	std::string username;
	std::string pw;
	Api api;

	//Login loop
	while (!loggedIn && !quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_BACKSPACE)
				{
					if (inputText.size() != 0)
					{
						inputText.pop_back();
					}
				}
				if (e.key.keysym.sym == SDLK_RETURN)
				{
					if (userNameScreen)
					{
						userNameScreen = false;
						pwScreen = true;
						username = inputText;
						inputText = "";
					}
					else if (pwScreen)
					{
						pwScreen = false;
						menuScreen = true;
						pw = inputText;
						api = Api(username, pw);
						inputText = "";
					}
				}
				if (menuScreen)
				{
					if (e.key.keysym.sym == SDLK_1)
					{
						menuScreen = false;
					}
					else if (e.key.keysym.sym == SDLK_2)
					{
						string gameSave = api.getGameSave();
						if (gameSave != "") {
							std::stringstream saved(gameSave);
							std::string holder;
							std::vector<std::string> input = std::vector<std::string>();
							while (std::getline(saved, holder, ',')) {
								input.push_back(holder);
							}
							if (input.size() == 3) {
								int score = atoi(input[0].c_str());
								int lives = atoi(input[1].c_str());
								int levelNum = atoi(input[2].c_str());
								game.load(score, lives, levelNum);
							}
						}
						menuScreen = false;
					}
				}
			}
			//Text input
			else if (e.type == SDL_TEXTINPUT)
			{
				if (inputText.size() < 20)
				{
					inputText += e.text.text;
				}
			}
		}
		if (userNameScreen)
		{
			gameView.userName(inputText);
		}
		else if (pwScreen)
		{
			gameView.password(inputText);
		}
		else if (menuScreen)
		{
			gameView.menu();
		}
		else
		{
			loggedIn = true;
		}
	}
	//end expensive operation
	SDL_StopTextInput();

	//Game loop
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (paused)
			{
				if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_r:
						paused = false;
						break;
					}
				}
			}
		}

		if (SDL_GetTicks() > enemyShootTimer + (FRAME_SPEED_ENEMY - (game.levelNum * 125)))
		{
			if (!paused)
				game.enemyShoot();
			enemyShootTimer = SDL_GetTicks();
		}

		if (!paused)
		{
			const uint8_t *currentKeyStates = SDL_GetKeyboardState(NULL);
			if (currentKeyStates[SDL_SCANCODE_RIGHT])
			{
				if (SDL_GetTicks() > player1MoveTimer + FRAME_SPEED_PLAYER)
				{
					move++;
				}
			}
			if (currentKeyStates[SDL_SCANCODE_LEFT])
			{
				if (SDL_GetTicks() > player1MoveTimer + FRAME_SPEED_PLAYER)
				{
					move--;
				}
			}
			if (currentKeyStates[SDL_SCANCODE_SPACE])
			{
				if (SDL_GetTicks() > player1ShotTimer + PLAYER_FIRE_RATE * 500)
				{
					player1ShotTimer = SDL_GetTicks();
					game.playerShoot();
				}
			}
			if (currentKeyStates[SDL_SCANCODE_P])
			{
				paused = true;
			}
		}

		if (SDL_GetTicks() > player1MoveTimer + FRAME_SPEED_PLAYER)
		{
			game.playerMove(move);
			player1MoveTimer = SDL_GetTicks();
			move = 0;
		}

		if (!paused)
			game.tick();
		std::vector<Blueprint> bps = game.getBlueprints();

		if (game.state == playing)
		{
			if (game.needsSave)
			{
				game.needsSave = false;
				std::string saveInput = "";
				saveInput += std::to_string(game.getScore()) + "," + std::to_string(game.getLives()) + "," + std::to_string(game.levelNum);
				api.setGameSave(saveInput);
			}
			gameView.render(bps, game.getScore(), game.getLives());
		}
		else if (game.state == won)
		{
			gameView.win();
		}
		else if (game.state == lost)
		{
			gameView.lose();
		}
	}

	//Cleanup
	gameView.close();
	return 0;
}
