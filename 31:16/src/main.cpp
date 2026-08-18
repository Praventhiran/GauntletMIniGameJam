#include "raylib.h"

int main()
{
    // INITIALIZATION

    //create the window here, with size and title
    InitWindow(1280, 720, "31:16");

    //tell raylib to run it 60fps
    SetTargetFPS(60);



    // PLAYER
    Vector2 playerPosition = { 640.0f, 360.0f };
    float playerSpeed = 300.0f;



    // GAME LOOP
   
    while (!WindowShouldClose())
    {

        // UPDATE

        //get the time between frames
        float deltaTime = GetFrameTime();

        // Move the player based on key pressed
        if (IsKeyDown(KEY_W))
        {
            playerPosition.y -= playerSpeed * deltaTime;
        }

        if (IsKeyDown(KEY_S))
        {
            playerPosition.y += playerSpeed * deltaTime;
        }

        if (IsKeyDown(KEY_A))
        {
            playerPosition.x -= playerSpeed * deltaTime;
        }

        if (IsKeyDown(KEY_D))
        {
            playerPosition.x += playerSpeed * deltaTime;
        }


        // DRAW

        //start drawing
        BeginDrawing();

        //clear the screen with a color
        ClearBackground(DARKGRAY);

        //draw a circle n player name
        DrawCircle(
            static_cast<int>(playerPosition.x),
            static_cast<int>(playerPosition.y),
            20,
            WHITE
        );

        DrawText(
            "PLAYER",
            static_cast<int>(playerPosition.x - 35),
            static_cast<int>(playerPosition.y - 45),
            15,
            WHITE
        );

        //stop drawing
        EndDrawing();


    }

    CloseWindow();

    return 0;
}