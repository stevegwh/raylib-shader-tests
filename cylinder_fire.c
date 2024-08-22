#include "raylib.h"
#include <stdlib.h>

#define GLSL_VERSION 330

const int screenWidth = 1280;
const int screenHeight = 720;

int main(void)
{
    const Vector2 screenSize = {.x = screenWidth, .y = screenHeight};
    // Initialization
    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - Shader Art Coding");

    // Create a RenderTexture2D to be used for render to texture
    RenderTexture2D target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    // Load shader and setup location points and values
    Shader shader = LoadShader(NULL, "resources/funkyfragment.fs");
    int secondsLoc = GetShaderLocation(shader, "seconds");
    int renderSizeLoc = GetShaderLocation(shader, "renderSize");
    SetShaderValue(shader, renderSizeLoc, &screenSize, SHADER_UNIFORM_VEC2);

    float seconds = 0.0f;
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        seconds += GetFrameTime();
        SetShaderValue(shader, secondsLoc, &seconds, SHADER_UNIFORM_FLOAT);

        // Draw
        // Using a render texture to draw
        BeginTextureMode(target);
        ClearBackground(BLACK);
        // Draw a rectangle in shader mode to be used as shader canvas
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
        EndTextureMode();

        BeginDrawing();

        ClearBackground(BLACK);

        // Begin shader mode
        BeginShaderMode(shader);
        DrawTextureV(target.texture, (Vector2){0, 0}, WHITE);
        EndShaderMode();

        EndDrawing();
    }

    // De-Initialization
    UnloadRenderTexture(target); // Unload render texture
    UnloadShader(shader);        // Unload shader

    CloseWindow(); // Close window and OpenGL context

    return 0;
}