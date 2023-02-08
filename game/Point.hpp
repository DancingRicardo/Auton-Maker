#pragma once
#include "raylib.h"

class Point {
private:

	Vector2 coords;

public:

	Point(Vector2 coordParams);

	void update();

	Vector2 getCoords();

};