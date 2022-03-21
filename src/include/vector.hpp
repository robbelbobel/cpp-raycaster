#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>

typedef struct vecf2d_s{
    float x;
    float y;
}vecf2d_t;

typedef struct vecf3d_s{
    float x;
    float y;
    float z;
}vecf3d_t;

typedef struct vecu2d_s{
    uint8_t x;
    uint8_t y;
}vecu2d_t;

#endif