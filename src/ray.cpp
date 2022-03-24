#include "include/ray.hpp"

Ray::Ray(vecf2d_t position){
    Ray::startPoint.position    = position;
    Ray::startPoint.direction   = 0;
    Ray::startPoint.textureID   = 0;

    Ray::endPoint = Ray::startPoint;
}

float Ray::getLength(){
    return sqrt(pow((Ray::endPoint.position.x - Ray::startPoint.position.x), 2) + pow((Ray::endPoint.position.y - Ray::startPoint.position.y), 2));
}

void Ray::cast(const level_t* level, const float angle){
    // Initialize Ray Copies
    Ray rayX(Ray::startPoint.position);
    Ray rayY(Ray::startPoint.position);

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
    
    Ray::endPoint.textureID = hit;

    if(rayX.getLength() < rayY.getLength()){
        Ray::endPoint.position = rayX.getEndPoint().position;
        Ray::endPoint.direction = dirX;
    }
    else{
        Ray::endPoint.position = rayY.getEndPoint().position;
        Ray::endPoint.direction = dirY;
    }
}

point_t Ray::getEndPoint(){
    return Ray::endPoint;
}

void Ray::extend(uint8_t dir, const float angle){
    switch(dir){
        case POINT_DIR_UP:
            Ray::endPoint.position.y = ceilf(Ray::endPoint.position.y) - 1;
            Ray::endPoint.position.x = Ray::startPoint.position.x + (Ray::startPoint.position.y - Ray::endPoint.position.y) / tanf(angle::toRad(angle));
            break;
        
        case POINT_DIR_DOWN:
            Ray::endPoint.position.y = floorf(Ray::endPoint.position.y) + 1;
            Ray::endPoint.position.x = Ray::startPoint.position.x + (Ray::startPoint.position.y - Ray::endPoint.position.y) / tanf(angle::toRad(angle));
            break;
        
        case POINT_DIR_LEFT:
            Ray::endPoint.position.x = ceilf(Ray::endPoint.position.x) - 1;
            Ray::endPoint.position.y = Ray::startPoint.position.y + (Ray::startPoint.position.x - Ray::endPoint.position.x) * tanf(angle::toRad(angle));
            break;
        
        case POINT_DIR_RIGHT:
            Ray::endPoint.position.x = floorf(Ray::endPoint.position.x) + 1;
            Ray::endPoint.position.y = Ray::startPoint.position.y + (Ray::startPoint.position.x - Ray::endPoint.position.x) * tanf(angle::toRad(angle));
            break;
        
        default:
            break;
    }
}

uint8_t Ray::checkCollision(const level_t* level, const uint8_t dir){
    uint8_t index;
    
    switch(dir){
        case POINT_DIR_UP:
            index = (Ray::endPoint.position.y - 1) * level -> size.x + (uint16_t) Ray::endPoint.position.x;
            break;

        case POINT_DIR_DOWN:
            index = Ray::endPoint.position.y * level -> size.x + (uint16_t) Ray::endPoint.position.x;
            break;

        case POINT_DIR_LEFT:
            index = (uint16_t) Ray::endPoint.position.y * level -> size.x + Ray::endPoint.position.x - 1;
            break;

        case POINT_DIR_RIGHT:
            index = (uint16_t) Ray::endPoint.position.y * level -> size.x + Ray::endPoint.position.x;
            break;
    }

    // Check If Index Is In Bounds
    if(index > level -> size.y * level -> size.x) return 0;

    return level -> wallMap[index];
}