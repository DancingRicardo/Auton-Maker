/*******************************************************************************************
*
*   raylib game template
*
*   <Game title>
*   <Game description>
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "screens.h"    // NOTE: Declares global (extern) variables and screens functions
#include "Field.hpp"
#include <iostream>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


static const int screenWidth = 800;
static const int screenHeight = 450;


//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Auton Developer");

    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop

    Field field;

    std::vector<Point> mainPointVector;

    static bool alreadyClicked = false;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
           
        ClearBackground(RAYWHITE);

        if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) {
            alreadyClicked = false;
        }
        
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !alreadyClicked) {
            mainPointVector.emplace_back(Point({ static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()) }));
            alreadyClicked = true;
        }

        if (IsKeyDown(KEY_ENTER)) {
            field.importSetPoints(&mainPointVector);
            std::cout << field.getAutonCode();

            
        }

        field.update();

        for (int i = 0; i < mainPointVector.size(); i++) {
            mainPointVector.at(i).update();
        }

        
        EndDrawing();

    }

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

