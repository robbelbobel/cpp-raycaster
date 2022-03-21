#ifndef LOADER_H
#define LOADER_H

#include <stdio.h>
#include <stdlib.h>

#include "level.hpp"

#define HEADER_SIZE 10

#define FILE_SIZE_PTR 3 * sizeof(uint8_t)
#define LEVEL_DATA_PTR 6 * sizeof(uint8_t)
#define TEXTURE_DATA_PTR 8 * sizeof(uint8_t)

level_t* loadLVL(const char* path);

void loadMap(level_t* level, const uint8_t* fileContent, const uint16_t mapDataAddress);
void loadTextures(level_t* level, const uint8_t* fileContent, const uint16_t textureDataAddress);

#endif
