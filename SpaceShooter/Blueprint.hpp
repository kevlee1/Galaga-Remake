#ifndef BLUEPRINT_HPP
#define BLUEPRINT_HPP

#include "Coordinate.hpp"
#include <string>

// struct that allows us to output each object with their sprite name - decouples model with view
// representation of the game state
struct Blueprint
{
    Coordinate location;
    std::string name;
};

#endif
