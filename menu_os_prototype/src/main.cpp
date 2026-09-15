#include "raylib.h"
#include "raymath.h"

int main() {

    InitWindow(1280, 720, "Menu Console Custom");

    // model & textures loading
    Model planet = LoadModel("../assets/planet.obj");
    Model stick_game = LoadModel("../assets/stick_game.obj");

    Model skybox = LoadModel("../assets/skybox_flip.obj");

    Texture2D texture = LoadTexture("../assets/texture.png");
    Texture2D texture2 = LoadTexture("../assets/stick_game.png");
    Texture2D texture3 = LoadTexture("../assets/space_box.png");

    planet.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    stick_game.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture2;
    skybox.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture3;

    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 0.0f, 5.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float speedY = 0.009f;

    Vector3 localStickPos = { 0.0f, 0.0f, 1.0f };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        bool isJPressed = IsKeyDown(KEY_J);

        rotationY += speedY;
        if (rotationY >= PI * 2.0f) rotationY -= PI * 2.0f;

        if (IsKeyDown(KEY_W)) rotationX -= 0.05f;
        if (IsKeyDown(KEY_S)) rotationX += 0.05f;
        if (IsKeyDown(KEY_A)) rotationY -= 0.05f;
        if (IsKeyDown(KEY_D)) rotationY += 0.05f;

        if (rotationX > 1.2f) rotationX = 1.2f;
        if (rotationX < -1.2f) rotationX = -1.2f;


        float wheel = GetMouseWheelMove();
        if (wheel != 0.0f) {
            camera.position.z -= wheel * 0.5f;
            if (camera.position.z < 1.5f) camera.position.z = 1.5f;
            if (camera.position.z > 15.0f) camera.position.z = 15.0f;
        }

        Matrix planetRotation = MatrixRotateXYZ((Vector3){ rotationX, rotationY, 0.0f });
        planet.transform = planetRotation;

        Vector3 stickerPosition = Vector3Transform(localStickPos, planetRotation);

        Matrix stickRotation = MatrixMultiply(MatrixRotateY(PI), planetRotation);
        stick_game.transform = stickRotation;

        BeginDrawing();

        ClearBackground(WHITE);


        BeginMode3D(camera);

        DrawModel(planet, (Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
        DrawModel(skybox, (Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
        DrawModel(stick_game, stickerPosition, 1.0f, WHITE);
        EndMode3D();

        DrawText("PROTOTYPE", 10, 10, 20, DARKBLUE);
        EndDrawing();

        // focus on sticker if J key is pressed
        if (isJPressed) {
            Vector3 dir = Vector3Normalize(stickerPosition);
            camera.position = Vector3Add(stickerPosition, Vector3Scale(dir, 3.0f));
            camera.target = stickerPosition;
            // On aligne le haut de la caméra sur l'axe "haut" de la planète pour être parfaitement droit
            camera.up = Vector3Transform((Vector3){ 0.0f, 1.0f, 0.0f }, planetRotation);
        }
    }


    UnloadTexture(texture);
    UnloadTexture(texture2);
    UnloadModel(planet);
    UnloadModel(skybox);
    UnloadModel(stick_game);

    CloseWindow();
    return 0;
}
