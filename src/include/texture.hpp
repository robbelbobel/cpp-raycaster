#ifndef TEXTURE_H
#define TEXTURE_H

#include "vector.hpp"

class Texture{
public:
    /** PUBLIC FUNCTIONS **/
    Texture(uint32_t** pixels, uint8_t frameCount, vecu2d_t size);
    
    uint32_t getPixel(const uint8_t x, const uint8_t y);
    vecu2d_t getSize();

    void update();

private:
    /** PRIVATE VARIABLES **/
    uint32_t** pixels;
    uint8_t frameCount;

    uint8_t currentFrame;

    vecu2d_t size;
};

#endif