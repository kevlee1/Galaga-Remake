#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "Coordinate.hpp"
#include "Blueprint.hpp"
#include <string>

// Base class for all entities that will need to handle collision in the 2d space
class Collidable
{
protected:
	Coordinate location;
	int size;
	int height;
	int width;


public:
	std::string spriteName;


	Collidable();
	Collidable(int x, int y, int size);
	Collidable(int x, int y, int width, int height);
	~Collidable();

	// getter for the size
	int getSize() const;
	int getWidth() const;
	int getHeight() const;

	// returns the coordinate
	const Coordinate &getLocation() const;

	// returns if this collidable is colliding with another collidable
	bool isColliding(const Collidable &c) const;

	// moves the collidable and changes it's location
	void move(int x, int y);

    // generates blueprint for all objects - representation of the model
	Blueprint generateBlueprint() const;
};

#endif
