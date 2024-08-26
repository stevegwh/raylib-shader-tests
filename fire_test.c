#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

#include "raymath.h" // Required for: Vector3, Quaternion and Matrix functionality
#include "rlgl.h"    // OpenGL abstraction layer to OpenGL 1.1, 2.1, 3.3+ or ES2
#include "utils.h"   // Required for: TRACELOG(), LoadFileData(), LoadFileText(), SaveFileText()

#include "external/par_shapes.h" // Shapes 3d parametric generation

#define GLSL_VERSION 330

const int screenWidth = 1280;
const int screenHeight = 720;

typedef struct sModel
{
    Model model;
    Vector3 pos;
} sModel;

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

    Texture2D texture = LoadTexture("../resources/textures/luos/Noise_Gradients/T_Random_53.png");
    Texture2D texture2 = LoadTexture("../resources/textures/luos/Noise_Gradients/T_Random_53.png");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    Shader shader =
        LoadShader("../resources/shaders/glsl330/rotation.vert", "../resources/shaders/glsl330/forcefield.frag");
    int secondsLoc = GetShaderLocation(shader, "seconds");
    float time = 0;
    shader.locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(shader, "texture1");

    Model sphere = LoadModel("../resources/models/obj/sphere.obj");

    DisableCursor();

    sModel models[5];
    for (int i = 0; i < 5; ++i)
    {
        sModel model;
        model.model = sphere;
        // model.model = LoadModelFromMesh(GenMeshCylinder(1, 1, 32));
        model.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
        // Using MATERIAL_MAP_EMISSION as a spare slot to use for 2nd texture
        model.model.materials[0].maps[MATERIAL_MAP_EMISSION].texture = texture2;
        model.model.materials[0].shader = shader;
        model.pos.x = 0;
        model.pos.y = 1;
        model.pos.z = -5 + i / 0.3f;
        models[i] = model;
    }

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        time += GetFrameTime();
        SetShaderValue(shader, secondsLoc, &time, SHADER_UNIFORM_FLOAT);

        UpdateCamera(&camera, CAMERA_FREE);

        // for (int i = 0; i < 5; ++i)
        // {
        //     models[i].pos.z -= 0.2f * GetFrameTime();
        // }

        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode3D(camera);

        for (int i = 0; i < 5; ++i)
        {
            DrawModelEx(models[i].model, models[i].pos, (Vector3){1, 0, 0}, 0, (Vector3){1, 1, 1}, WHITE);
        }

        DrawGrid(10, 1.0f); // Draw a grid
        EndMode3D();
        EndDrawing();
    }

    // De-Initialization

    UnloadTexture(texture);
    UnloadTexture(texture2);
    UnloadShader(shader);
    // UnloadModel(model);

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
