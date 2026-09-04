#include "raylib.h"
#include "raymath.h"

int main() {
    InitWindow(1280, 720, "Menu Console Custom");

    Model planet = LoadModel("planet.obj"); 
    Model stick_game = LoadModel("stick_game.obj");
    
    Texture2D texture = LoadTexture("texture.png"); 
    Texture2D texture2 = LoadTexture("stick_game.png");
    
    planet.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    stick_game.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture2; 

    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 0.0f, 5.0f }; 
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };  
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float rotationX = 0.0f;
    float rotationY = 0.0f;
    
    float speedY = 0.009f; 

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        rotationY += speedY;

        if (rotationY >= PI * 2.0f) rotationY -= PI * 2.0f;

        if (IsKeyDown(KEY_W)) rotationX -= 0.05f;
        if (IsKeyDown(KEY_S)) rotationX += 0.05f;
        if (IsKeyDown(KEY_A)) rotationY -= 0.05f;
        if (IsKeyDown(KEY_D)) rotationY += 0.05f;

        float wheel = GetMouseWheelMove(); 
        if (wheel != 0.0f) {
            camera.position.z -= wheel * 0.5f; 
            if (camera.position.z < 1.5f) camera.position.z = 1.5f;  
            if (camera.position.z > 15.0f) camera.position.z = 15.0f; 
        }

        Matrix rotationMatrix = MatrixRotateXYZ((Vector3){ rotationX, rotationY, 0.0f });
        planet.transform = rotationMatrix;
        stick_game.transform = rotationMatrix;

        Vector3 offset = { 0.0f, 0.0f, 0.0f };
        Vector3 stickerPosition = Vector3Transform(offset, rotationMatrix);

        BeginDrawing();
            ClearBackground(WHITE);

            BeginMode3D(camera);
                DrawModel(planet, (Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE); 
                DrawModel(stick_game, stickerPosition, 1.0f, WHITE);
            EndMode3D();

            DrawText("PROTOTYPE", 10, 10, 20, DARKBLUE);
        EndDrawing();
    }

    UnloadTexture(texture); 
    UnloadTexture(texture2); 
    UnloadModel(planet);
    UnloadModel(stick_game);
    
    CloseWindow();
    return 0;
}