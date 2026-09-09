#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "world_generation.h"

void draw_map(struct Map * map, Texture2D me, Texture2D house, Texture2D ground, Texture2D road, Texture2D building);

int main(void)
{
    InitWindow(1920, 1080, "This is my first game_mapttt!");

    Texture2D back = LoadTexture("back.png");
    Texture2D * generation = generate_static();
    if(generation == NULL) {
        fprintf(stderr,"Erreur generation\n");
        return EXIT_FAILURE;
    }

    Texture2D me = generation[0];
    Texture2D house = generation[1];
    Texture2D ground = generation[2];
    Texture2D road = generation[3];
    Texture2D building = generation[4];

    struct Map * game_map = generate_map("map_one");
    int accel = 0;

    int posX = game_map->SIZE_X / 2 * UNIT_SIZE;
    int posY = game_map->SIZE_Y / 2 * UNIT_SIZE;

    bool isacc = false;

    Camera2D camera = { 0 };
    camera.offset = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }; 
    camera.target = (Vector2){ posX + me.width, posY + me.height };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        
        if(IsKeyDown(KEY_LEFT_SHIFT) && isacc) {
            accel += 4;
            isacc = false;
        } 
        if(IsKeyUp(KEY_LEFT_SHIFT))  {
            accel = 0;
            isacc = true; 
        }

        if((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && (posX <= (game_map->SIZE_X * UNIT_SIZE - UNIT_SIZE))) {
            posX += 3 + accel;
        }
        if((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && ((float)posX >= -0.5f)) {
             posX -= 3 + accel;
        }
        if((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && (float)posY >= -0.5f) {
            posY -= 3 + accel;
        }
        if((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && posY <= (game_map->SIZE_Y * UNIT_SIZE - UNIT_SIZE)) {
            posY += 3 + accel;
        }
        
        // Mise à jour de la caméra
        camera.target = (Vector2){ (float)posX + me.width, (float)posY + me.height };
        camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove()*0.1f));
        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;
        
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(back, 0, 0, WHITE); 
            
            BeginMode2D(camera);
                draw_map(game_map, me, house, ground, road, building);

                Vector2 position = { (float)posX, (float)posY };
                DrawTextureEx(me, position, 0.0f, 2.0f, WHITE);  
            EndMode2D(); 

        EndDrawing();
    }
    
    UnloadTexture(back); 
    destruct_map(game_map);
    destruct_world(generation);
    CloseWindow();
    
    return EXIT_SUCCESS;
}

void draw_map(struct Map * map, Texture2D me, Texture2D house, Texture2D ground, Texture2D road, Texture2D building) {
    ClearBackground(DARKPURPLE);
    for(int i = 0; i < map ->SIZE_X ; ++i) {
        for(int j = 0; j < map-> SIZE_Y; ++j) {
            struct _64x64 x = map->map[i][j];
            Vector2 pos = {(float)x.posX, (float)x.posY};
            switch(x.texture_name) {
                case('H') : 
                DrawTextureEx(ground,pos,0.0f,2.0f,WHITE);
                DrawTextureEx(house,pos,0.0f,2.0f,WHITE);
                    break;
                case('R') : 
                DrawTextureEx(road,pos,0.0f,2.0f,WHITE);
                    break;
                case('G') :
                DrawTextureEx(ground,pos,0.0f,2.0f,WHITE);
                    break;
                case('M'):
                DrawTextureEx(me,pos,0.0f,2.0f,WHITE);
                    break;
                case('B'): 
                DrawTextureEx(ground,pos,0.0f,2.0f,WHITE);
                DrawTextureEx(building,pos,0.0f,2.0f,WHITE);
                default :
                    break;
            }
        }
    }
}