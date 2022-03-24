#include "include/texture.hpp"

Texture::Texture(uint32_t** pixels, uint8_t frameCount, vecu2d_t size){
    Texture::pixels = pixels;
    Texture::frameCount = frameCount;
    Texture::size = size;
    Texture::currentFrame = 0;
}

uint32_t Texture::getPixel(const uint8_t x, const uint8_t y){
    return Texture::pixels[Texture::currentFrame][y * Texture::size.x + x];
}

vecu2d_t Texture::getSize(){
    return Texture::size;
}

void Texture::update(){
    Texture::currentFrame = Texture::currentFrame >= (Texture::frameCount - 1) ? 0 : currentFrame + 1;
}