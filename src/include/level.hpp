#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "texture.hpp"

typedef struct level_s{
    vecu2d_t size;

    uint8_t type;
    
    uint8_t* wallMap;
    uint8_t* floorMap;
    uint8_t* ceilMap;

    Texture* textures[256];
    uint8_t textureCount;
} level_t;

#endif