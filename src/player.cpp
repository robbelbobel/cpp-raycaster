#include "include/player.hpp"

// TODO
uint8_t hasCollided(const vecf3d_t* pos, const level_t* level){
    if((uint8_t) pos -> x > level -> size.x) return 1;
    if((uint8_t) pos -> y > level -> size.y) return 1;

    if(level -> wallMap[(uint8_t) (floor(pos -> y) * level -> size.x + pos -> x)] != 0) return 1;
    return 0;
}

Player::Player(){
    // Assign Class Variables
    Player::position.x = 1.5f;
    Player::position.y = 1.5f;
    Player::position.z = 0.5f;

    Player::angle = 0;
    Player::moveSpeed = 0.005f;
    Player::lookSpeed = 0.2f;
}

void Player::move(const uint8_t dir, const level_t* level, const uint16_t deltaTime){
    vecf3d_t newPos = Player::position;
    
    switch (dir){
        case DIR_LEFT:
            newPos.x -= sinf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;
            newPos.y -= cosf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;

            if(!hasCollided(&newPos, level)) Player::position = newPos;
            break;
        
        case DIR_RIGHT:
            newPos.x += sinf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;
            newPos.y += cosf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;

            if(!hasCollided(&newPos, level)) Player::position = newPos;
            break;

        case DIR_BACKWARD:
            newPos.x -= cosf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;
            newPos.y += sinf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;

            if(!hasCollided(&newPos, level)) Player::position = newPos;
            break;

        case DIR_FORWARD:
            newPos.x += cosf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;
            newPos.y -= sinf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;

            if(!hasCollided(&newPos, level)) Player::position = newPos;
            break;

        case ANGLE_LEFT:
            Player::angle = angle::adjust(Player::angle + Player::lookSpeed * deltaTime);
            break;
        
        case ANGLE_RIGHT:
            Player::angle = angle::adjust(Player::angle - Player::lookSpeed * deltaTime);
            break;
        
        default:
            break;
    }
}

vecf3d_t Player::getPosition(){
    return Player::position;
}

float Player::getAngle(){
    return Player::angle;
}
