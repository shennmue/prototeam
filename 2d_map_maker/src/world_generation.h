// world_generation.h : In this file, the functions related to the map generation. 
// ------------------------------------------------------------------------------

#include <raylib.h>
#include <stdbool.h>


#define ELEMENT_SIZE 5
#define LIMIT_X_GENERATION 64 * 33 // X set to 0 when LIMIT_X_GENREATION reached 
#define LIMIT_Y_GENERATION 64 * 8 // Stop loop when LIMIT_Y_GENERATION reached 

#define FACTOR 2 // Factor to scale the textures.
#define UNIT_SIZE 64 * FACTOR // Each element of the map is a 64x64 texture.

// Each element of the map is a 64x64 texture.
// Ill use it to parse the file "map_one"
struct _64x64 {
    Texture2D texture;
    int posX;
    int posY;
    bool ishouse;
    char texture_name;
};

// A map is a two dimension array of _64x64 struct.
struct Map {
    int SIZE_X;
    int SIZE_Y;
    struct _64x64 **map;
};

// generate : Load the textures for each strings present in s.  
void generate(char ** s);

// generate_static : Load the textures from some pics for testing and return an 
//                   array which contains different parts. 
//                   Array[0] =  player_sprite
//                   Array[1] =  House 
//                   Array[2] =  ground
//                   Array[3] =  road
Texture2D * generate_static();

// destruct_world : Free the tab. 
void destruct_world(Texture2D * tab);

// generate_map : Convert the map in the file filename into a real map. 
struct Map * generate_map(const char *filename);

// destruct_map : Free the map.
void destruct_map(struct Map * map);