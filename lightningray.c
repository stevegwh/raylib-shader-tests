#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <stdlib.h>

#define GLSL_VERSION 330

const int screenWidth = 1280;
const int screenHeight = 720;

int main(void)
{
    // Define the camera to look into our 3d world
    Camera camera = {0};
    camera.position = (Vector3){0.0f, 1.0f, 2.0f}; // Camera position
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};   // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};       // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                           // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;        // Camera projection type

    const Vector2 screenSize = {.x = screenWidth, .y = screenHeight};
    // Initialization
    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - Shader Art Coding");

    Texture2D texture = LoadTexture("../resources/textures/luos/Noise_Gradients/T_Random_59.png");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    Shader shader = LoadShader(NULL, "../resources/shaders/custom/fire.fs");
    int secondsLoc = GetShaderLocation(shader, "seconds");
    float time = 0;

    Rectangle sourceRec = {0.0f, 0.0f, (float)texture.width, (float)texture.height};

    DisableCursor();

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        time += GetFrameTime();
        SetShaderValue(shader, secondsLoc, &time, SHADER_UNIFORM_FLOAT);

        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
        ClearBackground(BLUE);
        BeginMode3D(camera);

        // DrawBillboard(camera, texture, Vector3Zero(), 1.0f, WHITE);
        DrawBillboardPro(camera, texture, sourceRec, Vector3Zero(), (Vector3){0, 1, 0}, (Vector2){1, 1},
                         (Vector2){0, 0}, 43, WHITE);

        



        DrawGrid(10, 1.0f); // Draw a grid
        EndMode3D();
        EndDrawing();
    }

    // De-Initialization

    UnloadTexture(texture);
    UnloadShader(shader);

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
