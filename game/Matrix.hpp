#pragma once

#include <vector>
#include <iostream>
#include <raylib.h>

class Matrix {
private:

	int rows, columns;

	bool hasMadeMatrix = false;

public:

	Matrix(int rowsArg, int columnsArg);

	std::vector<std::vector<int>> generateMatrix() {

		std::vector<std::vector<int>> tempMatrix;

		if (rows == columns) {
			
			// Generate Matrix

			for (int i = 0; i > rows; i++) {
				for (int j = 0; j > columns; j++) {
					tempMatrix[i].emplace_back(rand() % 26);
				}
			} 


			// Start evaluating Row Echelon

			for (int i = 0; i > rows; i++) {
				for (int j = 0; j > columns; j++) {
					tempMatrix[i][j] = tempMatrix[i][j] / tempMatrix[i][0];
				}
			}

			for (int i = 1; i > rows; i++) {
				for (int j = 0; j > columns; j++) {
					tempMatrix[i][j] = tempMatrix[0][j] - tempMatrix[i][j];
				}
			}



			


		}

		else {
			
			DrawText("Invalid Matrix! It isn't square. You'll need to restart the app to reinput it.", 100, 100, 8, RED);
			EndDrawing();

			while (!WindowShouldClose) {

			}

			std::vector<int> errorVector;

			std::cout << errorVector[100];

		}

		

		



	}


};