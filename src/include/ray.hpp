#ifndef RAY_H
#define RAY_H

#include <math.h>

#include "player.hpp"
#include "point.hpp"

#define DOF 32

class Ray{
public:
    /* PUBLIC FUNCTIONS */
    Ray(vecf2d_t position);

    float getLength();
    void cast(const level_t* level, const float angle);
    point_t getEndPoint();

private:
    /* PRIVATE FUNCTIONS */
    void extend(uint8_t dir, const float angle);
    uint8_t checkCollision(const level_t* level, const uint8_t dir);

    /* PRIVATE VARIABLES */
    point_t startPoint;
    point_t endPoint;
};

#endif