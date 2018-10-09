
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cmath>
#include <string>
#include <map>
#include "View.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const std::string SPRITE_FILE = "Images/sprites.png";
const char *FONT_FILE = "Images/font.ttf";
const char *WINDOW_NAME = "SpaceShooter";

class LTexture
{
  public:
	//basic constructor
	LTexture();

	//destructor
	~LTexture();

	//Loads an image from file
	bool loadFromFile(std::string path);

	//loads an image given text
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, int flag);

	//destroys allocated texture
	void free();

	//renders sprite
	void render(int x, int y, SDL_Rect *clip = NULL);

	//renders text
	void renderText(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//set a color
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//set blending
	void setBlendMode(SDL_BlendMode blending);

	//set alpha
	void setAlpha(Uint8 alpha);

	//Gets image dimensions
	int getWidth();
	int getHeight();

  private:
	SDL_Texture *mTexture;
	int mWidth;
	int mHeight;
};

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

//Sprite textures
LTexture gSpriteSheetTexture;
//font textures
LTexture gFontTexture;
//Globally used fonts
TTF_Font *bigFont = NULL;
TTF_Font *smallFont = NULL;
//Globally used music
Mix_Music *music = NULL;

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	free();

	SDL_Texture *newTexture = NULL;

	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, int flag)
{
	free();
	SDL_Surface *textSurface;

	if (flag == 18)
	{
		textSurface = TTF_RenderText_Solid(smallFont, textureText.c_str(), textColor);
	}
	else
	{
		textSurface = TTF_RenderText_Solid(bigFont, textureText.c_str(), textColor);
	}

	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}

void LTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, SDL_Rect *clip)
{
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

void LTexture::renderText(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}
void LTexture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

// ============================================= View ================================================

View::View()
{
	screen_height = SCREEN_HEIGHT;
	screen_width = SCREEN_WIDTH;
	gSpriteClips = std::map<std::string, SDL_Rect>();
	sprites = std::vector<Sprite>();
}

View::View(int width, int height)
{
	screen_height = height;
	screen_width = width;
	gSpriteClips = std::map<std::string, SDL_Rect>();
	sprites = std::vector<Sprite>();
}

View::~View()
{
}

void View::init()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

				//Initialize picture library
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError());
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				}
			}
		}
	}

	loadMedia();
	loadFonts();
	defineSprites();
	loadSprites();
}

void View::defineSprites()
{
	Sprite playerSprite = {"player", 0, 0, 58, 64};
	sprites.push_back(playerSprite);

	Sprite playerMissile = {"playerMissile", 67, 0, 15, 28};
	sprites.push_back(playerMissile);

	Sprite player2Sprite = {"player2", 89, 0, 58, 64};
	sprites.push_back(player2Sprite);

	Sprite enemyMissile = {"enemyMissile", 67, 34, 15, 27};
	sprites.push_back(enemyMissile);

	Sprite enemy1Sprite = {"enemy1", 152, 0, 54, 42};
	sprites.push_back(enemy1Sprite);

	Sprite enemy2Sprite = {"enemy2", 152, 43, 54, 42};
	sprites.push_back(enemy2Sprite);

	Sprite enemy3Sprite = {"enemy3", 93, 64, 54, 59};
	sprites.push_back(enemy3Sprite);

	Sprite boss1 = {"boss1", 152, 87, 108, 115};
	sprites.push_back(boss1);

	Sprite bossMissile = {"bossMissile", 29, 71, 25, 45};
	sprites.push_back(bossMissile);

	Sprite powerUpLife = {"powerupLife", 206, 0, 29, 25};
	sprites.push_back(powerUpLife);

	Sprite powerUpShield = {"powerupShield", 207, 27, 28, 29};
	sprites.push_back(powerUpShield);

	Sprite powerUpSpeed = {"powerupSpeed", 234, 27, 28, 29};
	sprites.push_back(powerUpSpeed);

	Sprite playerLife = {"playerLife", 0, 64, 23, 27};
	sprites.push_back(playerLife);
}

void View::loadSprites()
{
	if (!gSpriteSheetTexture.loadFromFile(SPRITE_FILE))
	{
		printf("Failed to load sprite sheet texture!\n");
	}
	else
	{

		for (std::vector<Sprite>::const_iterator it = sprites.begin(); it != sprites.end(); ++it)
		{
			SDL_Rect spriteRectangle = {(*it).x, (*it).y, (*it).width, (*it).height};
			gSpriteClips[(*it).name] = spriteRectangle;
		}
	}
}

void View::loadFonts()
{
	bigFont = TTF_OpenFont(FONT_FILE, 48);
	if (bigFont == NULL)
	{
		printf("Failed to load big font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	smallFont = TTF_OpenFont(FONT_FILE, 18);
	if (smallFont == NULL)
	{
		printf("Failed to load small font! SDL_ttf Error: %s\n", TTF_GetError());
	}
}

void View::loadMedia()
{
	//Load music
	music = Mix_LoadMUS("Sounds/BG_MUSIC.ogg");
	if (music == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void View::close()
{
	//free images
	gSpriteSheetTexture.free();
	gFontTexture.free();

	//free fonts
	TTF_CloseFont(bigFont);
	bigFont = NULL;
	TTF_CloseFont(smallFont);
	smallFont = NULL;

	//free music
	Mix_FreeMusic(music);
	music = NULL;

	//free windows
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void View::render(std::vector<Blueprint> blueprints, int score, int lives)
{
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(gRenderer);

	std::string scoreText = "Score: " + std::to_string(score);

	SDL_Color textColor = {0xFF, 0xFF, 0xFF};
	if (!gFontTexture.loadFromRenderedText(scoreText, textColor, 18))
	{
		printf("Failed to render text texture!\n");
	}

	for (std::vector<Blueprint>::const_iterator it = blueprints.begin(); it != blueprints.end(); ++it)
	{
		if ((*it).name == "")
			continue;
		gSpriteSheetTexture.render((*it).location.x, (*it).location.y, &gSpriteClips[(*it).name]);
	}

	int currX = 15;
	int currY = 250;
	for (int i = 0; i < lives; ++i)
	{
		gSpriteSheetTexture.render(currX, currY, &gSpriteClips["playerLife"]);
		currX += 35;
	}
	gFontTexture.renderText(0, 0);

	SDL_RenderPresent(gRenderer);
}

void View::win()
{
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(gRenderer);

	SDL_Color textColor = {0xFF, 0xFF, 0xFF};
	if (!gFontTexture.loadFromRenderedText("You have won!", textColor, 48))
	{
		printf("Failed to render text texture!\n");
	}

	gFontTexture.renderText(350, 300);
	SDL_RenderPresent(gRenderer);
}

void View::lose()
{
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(gRenderer);

	SDL_Color textColor = {0xFF, 0xFF, 0xFF};
	if (!gFontTexture.loadFromRenderedText("GAME OVER", textColor, 48))
	{
		printf("Failed to render text texture!\n");
	}

	gFontTexture.renderText(400, 300);
	SDL_RenderPresent(gRenderer);
}

void View::playMusic()
{
	Mix_PlayMusic(music, -1);
}

void View::userName(std::string uName)
{
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(gRenderer);
	SDL_Color textColor = {0xFF, 0xFF, 0xFF};
	if (!gFontTexture.loadFromRenderedText("Username: " + uName, textColor, 18))
	{
		printf("Failed to render text texture!\n");
	}

	gFontTexture.renderText(400, 300);
	SDL_RenderPresent(gRenderer);
}

void View::password(std::string pw)
{
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(gRenderer);
	SDL_Color textColor = {0xFF, 0xFF, 0xFF};
	std::string asterisks = "";
	for (int i = 0; i < pw.length(); i++)
	{
		asterisks += "*";
	}
	if (!gFontTexture.loadFromRenderedText("Password: " + asterisks, textColor, 18))
	{
		printf("Failed to render text texture!\n");
	}

	gFontTexture.renderText(400, 300);
	SDL_RenderPresent(gRenderer);
}

void View::menu()
{
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(gRenderer);
	SDL_Color textColor = {0xFF, 0xFF, 0xFF};
	if (!gFontTexture.loadFromRenderedText("(1)New Game", textColor, 18))
	{
		printf("Failed to render text texture!\n");
	}
	gFontTexture.renderText(400, 300);

	if (!gFontTexture.loadFromRenderedText("(2)Load Saved Game (If available)", textColor, 18))
	{
		printf("Failed to render text texture!\n");
	}
	gFontTexture.renderText(400, 330);
	SDL_RenderPresent(gRenderer);
}
