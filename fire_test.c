#include "raylib.h"
#include "raymath.h"
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

    Texture2D texture = LoadTexture("../resources/textures/luos/Noise_Gradients/T_Random_50.png");
    Texture2D texture2 = LoadTexture("../resources/textures/luos/Noise_Gradients/T_Random_45.png");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    // Model model = LoadModelFromMesh(GenMeshSphere(0.5, 32, 32));
    // Model model = LoadModelFromMesh(GenMeshCylinder(1, 1, 32));
    Model model = LoadModelFromMesh(GenMeshPlane(1, 1, 1, 1));

    Shader shader = LoadShader(NULL, "../resources/shaders/glsl330/rotation.frag");
    int secondsLoc = GetShaderLocation(shader, "seconds");
    float time = 0;

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    // Using MATERIAL_MAP_EMISSION as a spare slot to use for 2nd texture
    model.materials[0].maps[MATERIAL_MAP_EMISSION].texture = texture2;
    shader.locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(shader, "texture1");
    model.materials[0].shader = shader;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        time += GetFrameTime();
        SetShaderValue(shader, secondsLoc, &time, SHADER_UNIFORM_FLOAT);

        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);

        // DrawModel(model, Vector3Zero(), 1.0f, WHITE);
        DrawModelEx(model, (Vector3){0, 1, 0}, (Vector3){1, 0, 0}, 90, (Vector3){1, 1, 1}, WHITE);

        DrawGrid(10, 1.0f); // Draw a grid
        EndMode3D();
        EndDrawing();
    }

    // De-Initialization

    UnloadTexture(texture);
    UnloadTexture(texture2);
    UnloadShader(shader);
    UnloadModel(model);

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
