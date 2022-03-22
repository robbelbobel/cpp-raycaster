#include "include/player.hpp"

Player::Player(){
    // Assign Class Variables
    Player::hitbox.position.x = 1.5f;
    Player::hitbox.position.y = 1.5f;
    Player::hitbox.position.z = 0.5f;
    
    Player::hitbox.size.x = 0.5f;
    Player::hitbox.size.y = 0.5f;

    Player::angle = 0;
    Player::moveSpeed = 0.005f;
    Player::lookSpeed = 0.2f;
}

void Player::move(const uint8_t dir, const level_t* level, const uint16_t deltaTime){
    vecf3d_t oldPos = Player::hitbox.position;
    
    switch (dir){
        case DIR_LEFT:
            Player::hitbox.position.x -= sinf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;
            Player::hitbox.position.y -= cosf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;

            if(hasCollided(Player::hitbox, level)) Player::hitbox.position = oldPos;
            break;
        
        case DIR_RIGHT:
            Player::hitbox.position.x += sinf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;
            Player::hitbox.position.y += cosf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;

            if(hasCollided(Player::hitbox, level)) Player::hitbox.position = oldPos;
            break;

        case DIR_BACKWARD:
            Player::hitbox.position.x -= cosf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;
            Player::hitbox.position.y += sinf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;

            if(hasCollided(Player::hitbox, level)) Player::hitbox.position = oldPos;
            break;

        case DIR_FORWARD:
            Player::hitbox.position.x += cosf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;
            Player::hitbox.position.y -= sinf(angle::toRad(Player::angle)) * Player::moveSpeed * deltaTime;

            if(hasCollided(Player::hitbox, level)) Player::hitbox.position = oldPos;
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
    return Player::hitbox.position;
}

float Player::getAngle(){
    return Player::angle;
}
