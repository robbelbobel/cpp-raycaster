#ifndef POINT_HPP
#define POINT_HPP

#include "vector.hpp"

enum pointDir_e{
    POINT_DIR_UP,
    POINT_DIR_DOWN,
    POINT_DIR_LEFT,
    POINT_DIR_RIGHT
};

struct point_s{
    uint8_t textureID;
    uint8_t direction;

    vecf2d_t position;
} typedef point_t;

#endif