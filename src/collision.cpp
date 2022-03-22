#include "include/collision.hpp"

bool hasCollided(const hitbox_t hitbox, const level_t* level){
    // Check Whether Hitbox Is OOB
    if((hitbox.position.x + hitbox.size.x > level -> size.x) || (hitbox.position.x < 0)) return true; 
    if((hitbox.position.y + hitbox.size.y > level -> size.y) || (hitbox.position.y < 0)) return true;

    if(level -> wallMap[(uint8_t) (floor(hitbox.position.y - hitbox.size.y / 2) * level -> size.x + hitbox.position.x - hitbox.size.x / 2)] != 0) return true;
    if(level -> wallMap[(uint8_t) (floor(hitbox.position.y + hitbox.size.y / 2) * level -> size.x + hitbox.position.x + hitbox.size.x / 2)] != 0) return true;

    return false;
}