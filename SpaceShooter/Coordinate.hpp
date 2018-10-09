#ifndef COORDINATE_HPP
#define COORDINATE_HPP

// class to locate an object on a 2D plane
class Coordinate
{
  public:
	Coordinate();
	Coordinate(int x, int y);
	~Coordinate();

	// getter for the x position
	int getX() const;

	// getter for the y position
	int getY() const;

	// override the = operator
	Coordinate &operator=(const Coordinate &other);

	int x, y;
};

#endif
