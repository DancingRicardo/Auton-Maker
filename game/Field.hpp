#pragma once

#include "Point.hpp"
#include <vector>
#include <string>

class Field {
private:

	Texture2D fieldTexture;

	
	std::vector<Point>* robotPointVector;
	std::vector<Point>* discPointVector;

	

public: 

	static constexpr int fieldRealHeight = 3250; // Mm
	static constexpr int fieldRealWidth = 3250; // Mm

	static constexpr int fieldScreenHeight = 291; // real height / 11.16838
	static constexpr int fieldScreenWidth = 291;  // real width  / 11.16838

	Vector2 redGoalCoords = { 360, 130 };
	Vector2 blueGoalCoords = { 130, 360 };

	static constexpr Vector2 fieldDefCoords = { 100, 100 };

	Field(std::vector<Point>* robotPointVectorArg, std::vector<Point>* discPointVectorArg);

	void update();

	std::string getAutonCode();

};