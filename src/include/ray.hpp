#ifndef RAY_H
#define RAY_H

#include <math.h>

#include "player.hpp"

#define DOF 32

enum pointDir_e{
    POINT_DIR_UP,
    POINT_DIR_DOWN,
    POINT_DIR_LEFT,
    POINT_DIR_RIGHT
};

typedef struct pointData_s{
    uint8_t textureID;
    uint8_t direction;
} pointData_t;

class Ray{
public:
    /* PUBLIC FUNCTIONS */
    Ray(vecf2d_t position);

    float getLength();
    pointData_t cast(const level_t* level, const float angle);
    vecf2d_t getEndPoint();

private:
    /* PRIVATE FUNCTIONS */
    void extend(uint8_t dir, const float angle);
    uint8_t checkCollision(const level_t* level, const uint8_t dir);

    /* PRIVATE VARIABLES */
    vecf2d_t position1;
    vecf2d_t position2;
};

#endif