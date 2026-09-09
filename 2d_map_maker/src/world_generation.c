#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "world_generation.h"


// To do : Loop on an img directory to feed our array :)
//         im just testing some shits
Texture2D * generate_static() {
    Texture2D * tab = malloc(sizeof(Texture2D) * ELEMENT_SIZE);
    if(tab ==  NULL) {
        fprintf(stderr,"Erreur d'allocation malloc\n");
        return NULL;
    }

    Texture2D me = LoadTexture("sprite2.png");
    Texture2D house = LoadTexture("house2.png");
    Texture2D ground = LoadTexture("ground_df.png");
    Texture2D road = LoadTexture("road_df.png");
    Texture2D building = LoadTexture("building.png");

    tab[0] = me;
    tab[1] = house;
    tab[2] =  ground;
    tab[3] =  road;
    tab[4] = building;
    return tab;
}

void destruct_world(Texture2D * tab) {
    for(int i = 0; i < ELEMENT_SIZE; ++i) {
        UnloadTexture(tab[i]);
    }
    free(tab);
}



struct Map * generate_map(const char * filename) {
    FILE * f =fopen(filename,"r");
    if(f == NULL) {
        fprintf(stderr,"Erreur ouverture fichier\n");
        return NULL;
    }
    struct Map * parsed_map = malloc(sizeof(struct Map));

    char line[256];
    fscanf(f,"%s",line);
    size_t LIMIT_X = strlen(line);
    size_t LIMIT_Y = 0;
    int r = 0;
    while(r != EOF) {
        r = fscanf(f,"%s",line);
        LIMIT_Y += 1;
    }
    fseek(f,0,SEEK_SET);

    parsed_map -> SIZE_X= LIMIT_X;
    parsed_map -> SIZE_Y = LIMIT_Y; 

    parsed_map->map = malloc(sizeof(struct _64x64 *) * LIMIT_X);
    if(parsed_map->map == NULL) {
        fprintf(stderr,"Erreur d'allocation malloc\n");
        return NULL;
    }
    for(int i = 0; i < LIMIT_X; ++i) {
        parsed_map->map[i] = malloc(sizeof(struct _64x64) * LIMIT_Y);
        if(parsed_map->map[i] == NULL) {
            fprintf(stderr,"Erreur d'allocation malloc\n");
            return NULL;
        }
    }

    int x = 0;
    int y = 0;
    int posX = 0;
    int posY = 0;
    char c;

    while((c = fgetc(f)) != EOF) {
        if(c == '\n') {
            y++;
            x = 0;
            posX = 0;
            posY += UNIT_SIZE;
            continue;
        }
        
        if(x < LIMIT_X && y < LIMIT_Y) {
            switch(c) {
                case 'H':
                    parsed_map->map[x][y].ishouse = true;
                    parsed_map->map[x][y].texture_name = 'H';
                    break;
                case 'B':
                    parsed_map->map[x][y].ishouse = true;
                    parsed_map->map[x][y].texture_name = 'B';
                    break;
                case 'G':
                    parsed_map->map[x][y].ishouse = false;
                    parsed_map->map[x][y].texture_name = 'G'; 
                    break;
                case 'R':
                    parsed_map->map[x][y].ishouse = false;
                    parsed_map->map[x][y].texture_name = 'R';
                    break;
                case 'M':
                    parsed_map->map[x][y].ishouse = false;
                    parsed_map->map[x][y].texture_name = 'M';
                    break;
                default:
                    continue; 
            }

            parsed_map->map[x][y].posX = posX;
            parsed_map->map[x][y].posY = posY;
            
            posX += UNIT_SIZE;
            x++;
        }
    }
    
    fclose(f);
    return parsed_map;
}

void destruct_map(struct Map * map) {
    for(int i = 0; i < map->SIZE_X; ++i) {
        free(map->map[i]);
    }
    free(map->map);
    free(map);
}