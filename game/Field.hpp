#pragma once

#include "Point.hpp"
#include <vector>
#include <string>

class Field {
private:

	Texture2D fieldTexture;

	static constexpr int fieldRealHeight = 3250; // Mm
	static constexpr int fieldRealWidth = 3250; // Mm

	static constexpr int fieldScreenHeight = 650; // real height / 5
	static constexpr int fieldScreenWidth = 650;  // real width  / 5

	std::vector<Point>* pointVector;

public: 

	Field();

	void importSetPoints(std::vector<Point>* inputPointVector);

	void update();

	std::string getAutonCode();

};