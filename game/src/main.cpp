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
#include "raygui.h"
#include "screens.h"    // NOTE: Declares global (extern) variables and screens functions
#include "Field.hpp"
#include <iostream>
#include <algorithm>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


static const int screenWidth = 1000;
static const int screenHeight = 600;


//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Auton Developer");

    ToggleFullscreen();

    SetTargetFPS(60);      

    std::vector<Point> mainPointVector;

    std::vector<Point> discPointVector;

    Field field(&mainPointVector, &discPointVector);

    static bool alreadyClickedMouse = false;
    static bool alreadyClickedTAB = false;
    static bool alreadyClickedMouseDISC = false;
    static bool alreadyClickedBACKSPACE = false;

    static int lastMouseX = GetMouseX();
    static int lastMouseY = GetMouseY();

    //--------------------------------------------------------------------------------------

    // Main loop
       


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
           
        ClearBackground(RAYWHITE);

        if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) {
            alreadyClickedMouse = false;
            alreadyClickedMouseDISC = false;
        }
        
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !alreadyClickedMouse && !(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))) {
            
            
            if (CheckCollisionPointRec({ static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()) }, { field.fieldDefCoords.x, field.fieldDefCoords.y,
                (float)field.fieldScreenWidth, (float)field.fieldScreenHeight }) ) {
                    
                    mainPointVector.emplace_back(Point({ static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()) }));
            
            }
            
            alreadyClickedMouse = true;
        }

        if (IsKeyDown(KEY_ENTER)) {
            std::cout << field.getAutonCode();
            
        }

        if (IsKeyDown(KEY_TAB) && !alreadyClickedTAB) {
            //int pointVSize = mainPointVector.size();            
            ToggleFullscreen();
            alreadyClickedTAB = true;

        } 

        else {
            alreadyClickedTAB = false;
        }


        if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) && IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !alreadyClickedMouseDISC) {
            
           
            if (CheckCollisionPointTriangle({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())}, field.fieldDefCoords, field.redGoalCoords, {field.fieldDefCoords.x + field.fieldScreenWidth, field.fieldDefCoords.y + field.fieldScreenHeight})) {
                if ((GetMouseX() < field.fieldDefCoords.x + field.fieldScreenWidth || GetMouseY() > field.fieldDefCoords.y + field.fieldScreenHeight)) {
                    discPointVector.emplace_back(Point(field.redGoalCoords, true));
                }
               
            }
            else if (CheckCollisionPointTriangle({ static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()) }, field.fieldDefCoords, field.blueGoalCoords, { field.fieldDefCoords.x + field.fieldScreenWidth, field.fieldDefCoords.y + field.fieldScreenHeight })) {
                if ((GetMouseX() < field.fieldDefCoords.x + field.fieldScreenWidth || GetMouseY() > field.fieldDefCoords.y + field.fieldScreenHeight)) {
                    discPointVector.emplace_back(Point(field.blueGoalCoords, true));
                }
                
            }
                
            mainPointVector.back().shootDisc();
            alreadyClickedMouseDISC = true;
            //SetMousePosition(10, 10);

        }



        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S)) {
            if (mainPointVector.size() > 0) {
                SetMousePosition(mainPointVector.back().getCoords().x, GetMouseY());
            }
        }

        else {
            //lastMouseY = GetMouseY();
            lastMouseX = GetMouseX();
        }

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
            if (mainPointVector.size() > 0) {
                SetMousePosition(GetMouseX(), mainPointVector.back().getCoords().y);
            }
        }


        else {
            lastMouseY = GetMouseY();
            //lastMouseX = GetMouseX();
        }

        if (IsKeyDown(KEY_Q)) {
            
            if (mainPointVector.size() > 0) {
                SetMousePosition(mainPointVector.back().getCoords().x, mainPointVector.back().getCoords().y);
            }
            
        }

        









        bool buttonPressClearAuton = GuiButton({ 600, 100, 125, 50 }, "Click to clear auton!");

        if (IsKeyDown(KEY_DELETE) || buttonPressClearAuton) {
            mainPointVector.clear();
            discPointVector.clear();
        }

        if (IsKeyDown(KEY_BACKSPACE) && !alreadyClickedBACKSPACE && mainPointVector.size() > 0) {

            if (mainPointVector.back().getShootsDisc()) {
                mainPointVector.pop_back();
                discPointVector.pop_back();
                alreadyClickedBACKSPACE = true;
            }
            else {
                mainPointVector.pop_back();
                alreadyClickedBACKSPACE = true;
            }
            
        }

        else if (IsKeyUp(KEY_BACKSPACE)) {
            alreadyClickedBACKSPACE = false;
        }

        DrawText("DELETE = CLEAR AUTON", 100, 400, 12, DARKBLUE);
        DrawText("BACKSPACE = CLEAR LAST POINT", 100, 420, 12, DARKBLUE);
        DrawText("Q = GO TO LAST POINT", 100, 440, 12, DARKBLUE);
        DrawText("HOLD SHIFT TO SHOOT ", 100, 460, 12, DARKBLUE);
        DrawText("W/D TO LOCK INTO LAST POINT Y AXIS", 100, 480, 12, DARKBLUE);
        DrawText("A/S TO LOCK INTO LAST POINT X AXIS", 100, 500, 12, DARKBLUE);


        //GuiLabelButton({ 400, 400, 100, 100 }, "Click to clear auton!");

        

        field.update();

        for (int i = 0; i < mainPointVector.size(); i++) {
            mainPointVector.at(i).update(i);
        }

        for (int i = 0; i < discPointVector.size(); i++) {
            discPointVector.at(i).update(i);
        }

        
        EndDrawing();

        //std::cout << GetMousePosition().x << std::endl << GetMousePosition().y << std::endl;

    }

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

