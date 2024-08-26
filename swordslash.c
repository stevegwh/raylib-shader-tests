#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <stdbool.h>
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
    Texture2D texture2 = LoadTexture("../resources/textures/luos/Noise_Gradients/T_Random_45.png");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    Model sphere = LoadModelFromMesh(GenMeshSphere(0.25, 32, 32));
    Model model = LoadModel("../resources/models/obj/flattorus.obj");
    // Model model = LoadModelFromMesh(GenMeshCylinder(1, 1, 32));
    // Model model = LoadModelFromMesh(GenMeshPlane(1, 1, 1, 1));

    Shader shader = LoadShader(NULL, "../resources/shaders/custom/swordslash.fs");
    int secondsLoc = GetShaderLocation(shader, "seconds");
    float time = 0;

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    // Using MATERIAL_MAP_EMISSION as a spare slot to use for 2nd texture
    model.materials[0].maps[MATERIAL_MAP_EMISSION].texture = texture2;
    shader.locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(shader, "texture1");
    model.materials[0].shader = shader;

    DisableCursor();
    int angle;
    bool shouldPlay = 0;
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        time += GetFrameTime();

        SetShaderValue(shader, secondsLoc, &time, SHADER_UNIFORM_FLOAT);

        UpdateCamera(&camera, CAMERA_FREE);

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            time = 0;
            shouldPlay = true;
        }

        if (time > 0.3)
        {
            time = 0;
            shouldPlay = false;
        }

        BeginDrawing();
        ClearBackground(BLUE);
        BeginMode3D(camera);

        DrawModel(sphere, Vector3Zero(), 1.0f, WHITE);

        if (shouldPlay)
        {
            rlDisableBackfaceCulling();
            DrawModelEx(model, (Vector3){0, 0, 0}, (Vector3){0, 1, 0}, time * 1000, (Vector3){0.5, 0.5, 0.5}, WHITE);
            rlEnableBackfaceCulling();
        }

        DrawGrid(10, 1.0f); // Draw a grid
        EndMode3D();
        EndDrawing();
    }

    // De-Initialization

    UnloadTexture(texture);
    UnloadTexture(texture2);
    UnloadShader(shader);
    UnloadModel(model);
    UnloadModel(sphere);

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
