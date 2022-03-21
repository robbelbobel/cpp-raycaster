#include "include/angle.hpp"

float angle::toRad(const float angle){
    return (angle * M_PI) / 180;
}

float angle::adjust(const float angle){
    if(angle > 360) return (angle - 360);
    if(angle <= 0)  return (angle + 360);

    return angle;
}