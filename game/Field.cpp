#include "Field.hpp"
#include <cmath>
#include <iostream>

Field::Field(std::vector<Point>* robotPointVectorArg, std::vector<Point>* discPointVectorArg) {
	fieldTexture = LoadTexture("resources/field.png");
	robotPointVector = robotPointVectorArg;
	discPointVector = discPointVectorArg;

}


void Field::update() {

	int discShotIndex = 0;

	DrawTexture(fieldTexture, fieldDefCoords.x, fieldDefCoords.y, WHITE);

	DrawCircle(redGoalCoords.x, redGoalCoords.y, 3, RED);
	DrawCircle(blueGoalCoords.x, blueGoalCoords.y, 3, BLUE);

	if (robotPointVector->size() > 1) {
		
		for (int i = 1; i < robotPointVector->size(); i++) {

			float xCordInchesLast = robotPointVector->at(i - 1).getCoords().x;
			float yCordInchesLast = robotPointVector->at(i - 1).getCoords().y;

			float xCordInches = robotPointVector->at(i).getCoords().x;
			float yCordInches = robotPointVector->at(i).getCoords().y;

			DrawLine(xCordInchesLast, yCordInchesLast, xCordInches, yCordInches, YELLOW);

			if (discPointVector->size() > 0) {
				if (robotPointVector->at(i).getShootsDisc()) {
					DrawLine(xCordInches, yCordInches,
						discPointVector->at(discShotIndex).getCoords().x, discPointVector->at(discShotIndex).getCoords().y, BLUE);
				
					discShotIndex++;
				}
			}
			


		}

		DrawLineV(robotPointVector->at(robotPointVector->size() - 1).getCoords(), GetMousePosition(), RAYWHITE);

	}

}

std::string Field::getAutonCode() {
	
	std::string autonString;

	autonString += "// NEW AUTON\n\n";

	float lastRobotAngle = 0;

	int discShotIndex = 0;

	for (int i = 0; i < robotPointVector->size(); i++) {

		if (i == 0) {
			i++;
		}

		float xCordInchesLast = robotPointVector->at(i).getCoords().x * 11.16838 / 25.4f;
		float yCordInchesLast = robotPointVector->at(i).getCoords().y * 11.16838 / 25.4f;

		float xCordInches = robotPointVector->at(i - 1).getCoords().x * 11.16838 / 25.4f;
		float yCordInches = robotPointVector->at(i - 1).getCoords().y * 11.16838 / 25.4f;


		

		


		

	
		
		
		
		// Turn to

		autonString += "drivetrain->turnTo(";

		float turnAngle = atan2(xCordInches - xCordInchesLast, yCordInches - yCordInchesLast) * 180 / 3.1415;

		if (turnAngle < -180) {
			turnAngle += 360;
		}
		else if (turnAngle > 180) {
			turnAngle -= 360;
		}

		autonString += std::to_string(lastRobotAngle - turnAngle);

		lastRobotAngle = turnAngle;

		autonString += ");\n\n";		

		
		

		// Wait Function

		autonString += "pros::delay(300);\n\n";

		// Drive to

		autonString += "drivetrain->driveTo(";

		float driveDistance = sqrt(pow(xCordInches - xCordInchesLast, 2) + pow(yCordInches - yCordInchesLast, 2));

		autonString += std::to_string(driveDistance);

		autonString += ");\n\n";

		// Wait Function

		autonString += "pros::delay(300);\n\n";

		// Shoot Function

		if (discPointVector->size() > 0) {
			if (robotPointVector->at(i).getShootsDisc()) {
				autonString += "flywheelController.shoot();\n\n";
				discShotIndex++;
			}
		}


		// NEXT STEP

		autonString += "// NEXT STEP\n\n";

		std::cout << 1000;

	}

	autonString += "// SHOOT EXPANSION \n\n";

	autonString += "// END AUTON\n\n";

	WaitTime(1);

	return autonString;

}