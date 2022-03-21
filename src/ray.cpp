#include "include/ray.hpp"

Ray::Ray(vecf2d_t position){
    Ray::position1 = position;
    Ray::position2 = position;
}

float Ray::getLength(){
    return sqrt(pow((Ray::position2.x - Ray::position1.x), 2) + pow((Ray::position2.y - Ray::position1.y), 2));
}

pointData_t Ray::cast(const level_t* level, const float angle){
    // Initialize Ray Copies
    Ray rayX(Ray::position1);
    Ray rayY(Ray::position1);

    // Determine Ray Direction
    uint8_t dirX = roundf(angle::adjust(angle)) > 90 && roundf(angle::adjust(angle)) < 270 ? POINT_DIR_LEFT : POINT_DIR_RIGHT;
    uint8_t dirY = roundf(angle::adjust(angle)) > 0  && roundf(angle::adjust(angle)) < 180 ? POINT_DIR_UP   : POINT_DIR_DOWN;

    uint8_t hit = 0;
    uint8_t dof = DOF;

    // Extend Both Rays
    rayX.extend(dirX, angle);
    rayY.extend(dirY, angle);

    // Check Collision Shortest Ray
    if(rayX.getLength() < rayY.getLength()) hit = rayX.checkCollision(level, dirX);
    else hit = rayY.checkCollision(level, dirY);

    while(!hit && dof > 0){
        // Extend Shortest Ray
        if(rayX.getLength() < rayY.getLength()) rayX.extend(dirX, angle);
        else rayY.extend(dirY, angle);

        // Check Collision Shortest Ray
        if(rayX.getLength() < rayY.getLength()) hit = rayX.checkCollision(level, dirX);
        else hit = rayY.checkCollision(level, dirY);

        dof--;
    }
    
    pointData_t pointData;
    pointData.textureID = hit;

    if(rayX.getLength() < rayY.getLength()){
        Ray::position2 = rayX.getEndPoint();
        pointData.direction = dirX;
    }
    else{
        Ray::position2 = rayY.getEndPoint();
        pointData.direction = dirY;
    }

    return pointData;
}

vecf2d_t Ray::getEndPoint(){
    return Ray::position2;
}

void Ray::extend(uint8_t dir, const float angle){
    switch(dir){
        case POINT_DIR_UP:
            Ray::position2.y = ceilf(Ray::position2.y) - 1;
            Ray::position2.x = Ray::position1.x + (Ray::position1.y - Ray::position2.y) / tanf(angle::toRad(angle));
            break;
        
        case POINT_DIR_DOWN:
            Ray::position2.y = floorf(Ray::position2.y) + 1;
            Ray::position2.x = Ray::position1.x + (Ray::position1.y - Ray::position2.y) / tanf(angle::toRad(angle));
            break;
        
        case POINT_DIR_LEFT:
            Ray::position2.x = ceilf(Ray::position2.x) - 1;
            Ray::position2.y = Ray::position1.y + (Ray::position1.x - Ray::position2.x) * tanf(angle::toRad(angle));
            break;
        
        case POINT_DIR_RIGHT:
            Ray::position2.x = floorf(Ray::position2.x) + 1;
            Ray::position2.y = Ray::position1.y + (Ray::position1.x - Ray::position2.x) * tanf(angle::toRad(angle));
            break;
        
        default:
            break;
    }
}

uint8_t Ray::checkCollision(const level_t* level, const uint8_t dir){
    uint8_t index;
    
    switch(dir){
        case POINT_DIR_UP:
            index = (Ray::position2.y - 1) * level -> size.x + (uint16_t) Ray::position2.x;
            break;

        case POINT_DIR_DOWN:
            index = Ray::position2.y * level -> size.x + (uint16_t) Ray::position2.x;
            break;

        case POINT_DIR_LEFT:
            index = (uint16_t) Ray::position2.y * level -> size.x + Ray::position2.x - 1;
            break;

        case POINT_DIR_RIGHT:
            index = (uint16_t) Ray::position2.y * level -> size.x + Ray::position2.x;
            break;
    }

    // Check If Index Is In Bounds
    if(index > level -> size.y * level -> size.x) return 0;

    return level -> wallMap[index];
}