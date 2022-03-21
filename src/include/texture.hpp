#ifndef TEXTURE_H
#define TEXTURE_H

#include "vector.hpp"

typedef struct texture_s{
    uint32_t** pixelData;
    uint8_t frameCount;

    uint8_t currentFrame;

    vecu2d_t size;
} texture_t;

void updateTextures(texture_t* textures, uint8_t textureCount);

#endif