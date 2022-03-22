#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "math.h"
#include "hitbox.hpp"
#include "level.hpp"

bool hasCollided(const hitbox_t hitbox, const level_t* level);

#endif