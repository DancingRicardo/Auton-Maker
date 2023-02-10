#include "Point.hpp"



Point::Point(Vector2 coordParams, bool isDiscArg) {
	coords = coordParams;
	isDisc = isDiscArg;

} 

void Point::update(int index) {

	if (!isDisc) {
		if (index == 0) {
			DrawCircle(coords.x, coords.y, 3, GREEN);
		}
		else {
			DrawCircle(coords.x, coords.y, 3, PINK);
		}

	}

	else {
		DrawCircle(coords.x, coords.y, 3, DARKBLUE);
	}
	
}

void Point::shootDisc() {
	shootsDisc = true;
}

bool Point::getShootsDisc() {
	return shootsDisc;
}

Vector2 Point::getCoords() {
	return coords;
}
