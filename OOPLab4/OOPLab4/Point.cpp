#include "Point.h"
#include <sstream>

bool Point::operator==(const Point& other) const
{
	return (this->x == other.x) && (this->y == other.y);
}
