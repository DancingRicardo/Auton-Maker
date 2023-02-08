#include "Point.hpp"



Point::Point(Vector2 coordParams) {
	coords = coordParams;

}

void Point::update() {
	DrawCircle(coords.x, coords.y, 3, PINK);
}

Vector2 Point::getCoords() {
	return coords;
}
