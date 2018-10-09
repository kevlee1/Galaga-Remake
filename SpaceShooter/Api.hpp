#ifndef API_HPP
#define API_HPP

#include <string>

class Api
{
private:
  std::string username;
  std::string password;

public:
  Api();
  // Initialize the api with a username and password
  Api(std::string, std::string);
  // Return the saved game state as a string, otherwise return ""
  std::string getGameSave();
  // Attmempts to save the game state, return true on sucess
  bool setGameSave(std::string);
};

#endif
