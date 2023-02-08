#include "Field.hpp"
#include <cmath>
#include <iostream>

Field::Field() {
	fieldTexture = LoadTexture("resources/field.png");
}

void Field::importSetPoints(std::vector<Point>* inputPointVector) {
	pointVector = inputPointVector;
}

void Field::update() {
	DrawTexture(fieldTexture, 0, 0, WHITE);
}

std::string Field::getAutonCode() {
	
	std::string autonString;

	autonString += "// NEW AUTON\n\n";

	for (int i = 0; i < pointVector->size(); i++) {

		float xCordInches = pointVector->at(i).getCoords().x * 5 / 25.4f;
		float yCordInches = pointVector->at(i).getCoords().y * 5 / 25.4f;
	

		// Turn to

		autonString += "drivetrain->turnTo(";

		float turnAngle = atan(xCordInches / yCordInches);

		autonString += std::to_string(turnAngle);

		autonString += ");\n\n";

		// Wait Function

		autonString += "pros::delay(300);\n\n";

		// Drive to

		autonString += "drivetrain->driveTo(";

		float driveDistance = sqrt(pow(xCordInches, 2) + pow(yCordInches, 2));

		autonString += std::to_string(driveDistance);

		autonString += ");\n\n";

		std::cout << 1000;

	}

	autonString += "// END AUTON\n\n";

	WaitTime(1);

	return autonString;
}