#include "include/texture.hpp"

void updateTextures(texture_t* textures, uint8_t textureCount){
    for(uint8_t i = 0; i < textureCount; i++){
        textures[i].currentFrame = textures[i].currentFrame < (textures[i].frameCount - 1) ? textures[i].currentFrame + 1 : 0;
    }
}