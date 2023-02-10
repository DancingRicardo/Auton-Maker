#pragma once
#include "raylib.h"

class Point {
private:

	Vector2 coords;

	bool shootsDisc = false;
	bool isDisc = false;

public:

	Point(Vector2 coordParams, bool isDiscArg = false);

	void update(int index);

	void shootDisc();

	Vector2 getCoords();

	bool getShootsDisc();

};