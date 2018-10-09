#ifndef VIEW_HPP
#define VIEW_HPP

#include <vector>
#include <map>
#include <SDL.h>
#include "Sprite.hpp"
#include "Blueprint.hpp"

// class for the view
class View
{
public:
  View();
  View(int, int);
  ~View();
    // initializes the view
  void init();
    // closes the view
  void close();
    // renders the objects
  void render(std::vector<Blueprint>, int score, int lives);
    // renders the win screen
  void win();
    // renders the lose screen
  void lose();
    // plays background music
  void playMusic();
    // renders username entering
  void userName(std::string uName);
    // renders password entering
  void password(std::string pw);
    // renders menu
  void menu();
private:
  int screen_width;
  int screen_height;
  std::map<std::string, SDL_Rect> gSpriteClips;
  std::vector<Sprite> sprites;
    // defines sprites
  void defineSprites();
    // loads sprite
  void loadSprites();
    // loads fonts
  void loadFonts();
    // loads media
  void loadMedia();
};

#endif
