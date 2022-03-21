#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "vector.hpp"
#include "level.hpp"
#include "angle.hpp"

enum move_e{
    DIR_LEFT,
    DIR_RIGHT,
    DIR_BACKWARD,
    DIR_FORWARD,
    ANGLE_RIGHT,
    ANGLE_LEFT
};

class Player{
public:
    /* PUBLIC FUNCTIONS */
    Player();

    void move(const uint8_t dir, const level_t* level, const uint16_t deltaTime);
    vecf3d_t getPosition();
    float getAngle();

private:
    /* PRIVATE VARIABLES */
    vecf3d_t position;
    float moveSpeed;
    float lookSpeed;
    float angle;
};

#endif